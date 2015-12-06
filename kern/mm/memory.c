#include <kernel.h>

typedef struct {
    uint size;
    struct run* next;
} run;

run* free_head = NULL;

void init_mem() {
    uart_spin_puts("Initializing Memory.\r\n");
}
