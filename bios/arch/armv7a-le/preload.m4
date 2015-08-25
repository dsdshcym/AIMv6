changecom(`/*', `*/')
changequote([,])
/*
 * Copyright (C) 2015 David Gao <davidgao1001@gmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

sinclude([board.m4])
sinclude([chip.m4])

ENTRY(preload_vector)

SECTIONS
{
	. = 0x1FF00000; /* 511M */
	.text : {
		*vector.o(.text)
		*(.text .rodata)
	}
	.data : {
		*(.data)
	}
}
