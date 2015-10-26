#ifndef _KERNEL_H
#define _KERNEL_H

#include <config.h>
#include <drivers/serial/uart.h>
#include <drivers/sd/sd-zynq7000.h>
#include <asm/io.h>

uint KERN_BASE    = 0x80000000;
uint TABLE_ADDR   = 0X00014000;
uint KERNEL_ADDR  = 0X00200000;
uint INVALID_ADDR = 0X00800000;

#endif
