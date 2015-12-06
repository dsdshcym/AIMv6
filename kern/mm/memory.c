#include <kernel.h>

#define MIN_ADDR 0x800000
#define MAX_ADDR 0X1F000000
#define KSIZE    4096

struct run {
    uint size;
    struct run* next;
};

typedef struct run run;

run* free_head = NULL;

void init_mem() {
    free_head = (run*)MIN_ADDR;
    free_head->size = MAX_ADDR - MIN_ADDR;
    free_head->next = NULL;
}
