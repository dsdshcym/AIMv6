#ifndef _MMU_H
#define _MMU_H

#define TTB_FLAG 0x5E2
#define FIRST_TTB_VAL 0x155E6
#define SP_ADDR 0x20000000
#define SP_TOP 0x1F000000

#define L2CACHE_CONTROL 0xF8F02100
#define SCU_CONTROL 0xF8F00000

#define SECTION_RANGE 0x100000

void enable_MMU();

#endif
