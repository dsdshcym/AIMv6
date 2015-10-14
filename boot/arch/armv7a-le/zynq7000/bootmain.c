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
    volatile u8 *pte_2_p = (void *)pte_2;
    while(1);
}

