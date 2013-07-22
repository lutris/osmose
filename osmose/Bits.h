/*
 * Copyright 2001-2011 Vedder Bruno.
 *	
 * This file is part of Osmose, a Sega Master System/Game Gear software 
 * emulator.
 *
 * Osmose is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Osmose is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Osmose.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BITS_H
#define BITS_H

#define BIT0	0x1
#define BIT1	0x2
#define BIT2	0x4
#define BIT3	0x8
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

/* And with these value to force bit to zero */
#define BIT0_MASK 0xFE
#define BIT1_MASK 0xFD
#define BIT2_MASK 0xFB
#define BIT3_MASK 0xF7
#define BIT4_MASK 0xEF
#define BIT5_MASK 0xDF
#define BIT6_MASK 0xBF
#define BIT7_MASK 0x7F
#endif
