#include <kernel.h>
#include <mmu.h>
#include <memory.h>

uint KERN_BASE    = 0x80000000;
uint TABLE_ADDR   = 0X00014000;
uint KERNEL_ADDR  = 0X00200000;
uint INVALID_ADDR = 0X00800000;

int main() {
    uart_spin_puts("Entering Kernel!\r\n");

    uart_spin_puts("Enabling MMU.\r\n");
    enable_MMU();
    uart_spin_puts("MMU Enabled.\r\n");

    uart_spin_puts("Initialize Memory.\r\n");
    init_mem();
    uart_spin_puts("Memory Initialized.\r\n");
}
