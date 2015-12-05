/* This code is based on the work Chuming Lin has done
   All credit goes to him
*/

#include <mmu.h>
#include <kernel.h>

void invalidate_TLB() {
    uart_spin_puts("invalidate_TLB\r\n");

    /* armv7-a-r-manual.pdf::1497 */
    asm volatile(
                 "mov r0, #0\n\t"
                 /* Invalidate entire instruction TLB */
                 "mcr p15, 0, r0, c8, c5, 0\n\t"
                 "isb \n\t"
                 /* Invalidate entire data TLB */
                 "mcr p15, 0, r0, c8, c6, 0\n\t"
                 "isb \n\t"
                 /* Invalidate entire unified TLB */
                 "mcr p15, 0, r0, c8, c7, 0\n\t"
                 "isb\n\t"
                 );

    uart_spin_puts("invalidate_TLB Done\r\n");
}

void write_page(uint virtual_addr, uint physical_addr) {
    uint tmp = virtual_addr >> 20;
    uint addr = TABLE_ADDR + (tmp << 2);
    tmp = (physical_addr >> 20) << 20;
    out32(addr, (tmp + TTB_FLAG));
}

void create_first_page() {
    uart_spin_puts("create_first_page Begin\r\n");

    uint count = 0;
    uint i;

    for (i = 0; count < 4096; i += SECTION_RANGE, count++) {
        write_page(i, i);
    }

    for (i = 0; i < INVALID_ADDR; i += SECTION_RANGE) {
        write_page(i + KERN_BASE, i);
    }

    for (i = SP_TOP; i < SP_ADDR; i += SECTION_RANGE) {
        write_page(i + KERN_BASE, i);
    }
    out32(TABLE_ADDR, FIRST_TTB_VAL);

    uart_spin_puts("create_first_page Done\r\n");
}

void set_TTB() {
    uart_spin_puts("set_TTB\r\n");

    asm volatile(
                 "ldr r1, =TABLE_ADDR\n\t"
                 "ldr r0, [r1]\n\t"
                 "mcr p15, 0, r0, c2, c0, 0\n\t"
                 );

    uart_spin_puts("set_TTB Done\r\n");
}

void set_DOMAIN() {
    uart_spin_puts("set_DOMAIN\r\n");

    asm volatile(
                 "ldr r0, =0x55555555\n\t"
                 "mcr p15, 0, r0, c3, c0, 0\n\t"
                 );

    uart_spin_puts("set_DOMAIN Done\r\n");
}

void set_MMU() {
    uart_spin_puts("set_MMU\r\n");

    asm volatile(
                 "mrc p15, 0, r0, c1, c0, 0\n\t"
                 "orr r0, r0, #0x1\n\t"
                 "mcr p15, 0, r0, c1, c0, 0\n\t"
                 "isb\n\t"
                 );

    uart_spin_puts("set_MMU Done\r\n");
}

void set_SCU() {
    uart_spin_puts("set_SCU\r\n");

    out32(SCU_CONTROL, 0x3);

    uart_spin_puts("set_SCU Done\r\n");
}

void set_caches() {
    uart_spin_puts("set_caches\r\n");

    asm volatile(
                 "ldr r1, =0x1804\n\t"
                 "mrc p15, 0, r0, c1, c0, 0\n\t"
                 "orr r0, r0, r1\n\t"
                 "mrc p15, 0, r0, c1, c0, 0\n\t"
                 "isb\n\t"
                 );

    out32(L2CACHE_CONTROL, 0x1);

    uart_spin_puts("set_caches Done\r\n");
}

void update_PC() {
    uart_spin_puts("update_PC\r\n");

    asm volatile(
                 "ldr r0, =KERN_BASE\n\t"
                 "ldr r1, [r0]\n\t"
                 "add pc, pc, r1\n\t"
                 "isb\n\t"
                 );

    uart_spin_puts("update_PC Done\r\n");
}

void update_SP() {
    uart_spin_puts("update_SP\r\n");

    asm volatile(
                 "ldr r0, =KERN_BASE\n\t"
                 "ldr r1, [r0]\n\t"
                 "add sp, sp, r1\n\t"
                 "isb\n\t"
                 );

    uart_spin_puts("update_SP Done\r\n");
}

void clear_lower_address() {
    uart_spin_puts("clear_lower_address\r\n");

    uint i;
    for (i = 0; i < INVALID_ADDR; i += SECTION_RANGE) {
        uint offset = (i >> 20) << 2;
        out32(TABLE_ADDR + offset, 0);
    }

    uart_spin_puts("clear_lower_address Done\r\n");
}

void enable_MMU() {
    create_first_page();

    set_TTB();

    set_DOMAIN();

    set_MMU();

    invalidate_TLB();

    set_SCU();

    set_caches();

    update_PC();

    update_SP();

    clear_lower_address();
}
