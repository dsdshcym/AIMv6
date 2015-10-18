/*
 * Copyright (C) 2015 David Gao <davidgao1001@gmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#define ELF32

#include <config.h>
#include <elf.h>

#define PRELOAD_VECTOR_BASE	0x1ff00000

void (*uart_init)(void) = (void *)(PRELOAD_VECTOR_BASE + 0x4);
void (*uart_enable)(void) = (void *)(PRELOAD_VECTOR_BASE + 0x8);
void (*uart_spin_puts)(const char *) = (void *)(PRELOAD_VECTOR_BASE + 0xC);
void (*puthex)(u32 num) = (void *)(PRELOAD_VECTOR_BASE + 0x10);
int (*sd_dma_spin_read)(u32 pa, u16 count, u32 offset) = (void *)(PRELOAD_VECTOR_BASE + 0x14);

void mbr_bootmain(void) {
    /* mbr was already read in firmware_bootmain */
    volatile u8 *mbr = (void *)0x100000;

    u16 i;
    u32 pte_2 = 0;
    for (i = 11; i > 7; i--) {
        pte_2 <<= 8;
        pte_2 += mbr[462 + i];
    }
    /* uart_spin_puts("PTE2:\n"); */
    /* puthex(pte_2); */
    volatile u8 *partition_2 = (void *)0x200000;
    int ret;
    ret = sd_dma_spin_read((u32)partition_2, 1, pte_2);
    if (ret != 0) {
        uart_spin_puts("ERROR: sd_read failed with error #");
        puthex(ret);
        while(1);
    }
    elf32hdr_t elf = *(elf32hdr_t *)partition_2;

    elf32_phdr_t program_header = *(elf32_phdr_t *)(partition_2 + elf.e_phoff);

    u32 offset = (u32)((program_header.p_offset >> 9) + pte_2);
    u32 begin = (u32)(program_header.p_offset & 511);

    volatile u8 *kernel = (void *)(elf.e_entry);

    ret = sd_dma_spin_read((u32)kernel, 1, offset);
    if (ret != 0) {
        uart_spin_puts("ERROR: sd_read failed with error #");
        puthex(ret);
        while(1);
    }

    void (*kernel_entry)() = (void *)(kernel + begin);

    kernel_entry();

    while(1);
}
