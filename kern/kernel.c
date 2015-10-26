#include "kernel.h"
#include "mmu.h"

int main() {
    uart_spin_puts("Entering Kernel!\r\n");

    uart_spin_puts("Enabling MMU.\r\n");
    enable_MMU();
    uart_spin_puts("MMU Enabled.\r\n");
}
