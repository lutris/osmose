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
 
#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/*
	Uncomment and rebuild project for integrated debugger
   	Don't forget to uncomment OPT_OBJS line in Makefile before compiling.
*/
//#define BUILT_IN_DEBUGGER

//#define AUTO_SCREENSHOT

/* Number of Z80 cycles for each scanline. */
#define CPU_CYCLES_PER_LINE        228

/* SDL delay every 3 frames.*/
#define DELAY_BETWEEN_FRAME        50

/* SDL Sound buffer size for samples. */
#define SAMPLE_SIZE                1024      // Sample duration is 23ms

/**/
#define SND_TOGGLE                 0.4026717557251908  // rest of 367.5/262.

/* Uncomment this line for verbose information on PSG/VDP access */
//#define PSG_VERBOSE
//#define VDP_ACCESS
//#define AUTO_NAT_VERBOSE
//#define PAD_VERBOSE
//#define MEM_CTRL_VERBOSE
/* Just uncomment this define to get trace of bank mapping operations */
//#define P_VERBOSE

#endif
