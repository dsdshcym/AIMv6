#include <kernel.h>

#define TTB_FLAG 0x5E2
#define FIRST_TTB_VAL 0x155E6
#define SP_ADDR 0x20000000
#define SP_TOP 0x1F000000

#define L2CACHE_CONTROL 0xF8F02100
#define SCU_CONTROL 0xF8F00000

uint SECTION_RANGE = 0x100000;

void invalidate_TLB() {
    uart_spin_puts("invalidate_TLB\r\n");
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
                 "ldr r0, =TABLE_ADDR\n\t"
                 "mcr p15, 0, r0, c2, c0, 0\n\t"
                 );

    uart_spin_puts("set_TTB Done\r\n");
}

void set_DOMAIN() {
    uart_spin_puts("set_DOMAIN\r\n");
}

void set_MMU() {
    uart_spin_puts("set_MMU\r\n");
}

void set_SCU() {
    uart_spin_puts("set_SCU\r\n");
}

void set_caches() {
    uart_spin_puts("set_caches\r\n");
}

void enable_MMU() {
    create_first_page();

    set_TTB();

    set_DOMAIN();

    set_MMU();

    invalidate_TLB();

    set_SCU();

    set_caches();
}
