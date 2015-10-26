#include <kernel.h>

#define TTB_FLAG 0x5E2
#define FRIST_TTB_VAL 0x155E6
#define SP_ADDR 0x20000000
#define SP_TOP 0x1F000000

#define L2CACHE_CONTROL 0xF8F02100
#define SCU_CONTROL 0xF8F00000

void invalidate_TLB() {
    uart_spin_puts("invalidate_TLB\r\n");
}

void create_first_page() {
    uart_spin_puts("create_first_page\r\n");
}

void set_TTB() {
    uart_spin_puts("set_TTB\r\n");
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
