#ifndef _KERNEL_H
#define _KERNEL_H

#include <config.h>
#include <drivers/serial/uart.h>
#include <drivers/sd/sd-zynq7000.h>
#include <asm/io.h>

extern uint KERN_BASE;
extern uint TABLE_ADDR;
extern uint KERNEL_ADDR;
extern uint INVALID_ADDR;

#endif
