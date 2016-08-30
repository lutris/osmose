/*****************************************************************************
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
 *
 * File: VDP_GG.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle SMS's VDP (Video Display Processor)operation.
 *
 * Author: Vedder Bruno
 * Date: 25/10/2006, 19h15
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef VDP_H
#define VDP_H

#include "Definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include "Bits.h"
#include "Options.h"
#include "Z80.h"
#include "DebugEventThrower.h"
#include "SaveState.h"
#include "AnsiColorTerminal.h"

using namespace std;

extern EmulatorOptions emu_opt;

/* Uncomment this to display sprites */
#define DISPLAY_SPRITES

#define VDP_REGISTER_NBR        16

/* Destination component when data port is written */
#define D_VRAM                        0
#define D_CRAM                        1

#define REG0 regs [0]
#define REG1 regs [1]
#define REG2 regs [2]
#define REG3 regs [3]
#define REG4 regs [4]
#define REG5 regs [5]
#define REG6 regs [6]
#define REG7 regs [7]
#define REG8 regs [8]
#define REG9 regs [9]
#define REG10 regs [10]

/*Uncomment this to have VDP access trace */
//#define VDP_VERBOSE

typedef struct
{

    unsigned short map_addr;
    unsigned short sit_addr;
    unsigned char  regs[VDP_REGISTER_NBR];
    unsigned char  vdp_status;
    unsigned char  v_counter;
    int line;
    unsigned char     i_counter;
    unsigned char  rd_data_port_buffer;
    bool irq_line_pending;
    bool vsynch_irq_pending;
    bool sms_irq;
    unsigned char  latch;
    unsigned short addr;
    unsigned char  cmd_type;
    bool           cmd_flag;

} VDPSaveState;


class VDP : public DebugEventThrower, public ImplementsSaveState
{

    public:

        VDP(Z80 *c,bool ntsc);
        virtual ~VDP() {};
        virtual void writeDataPort(unsigned char data); // Port 0xBE written (overriden VDP_GG).
        unsigned char readDataPort();                   // Port 0xBE read.
        void writeCtrlPort(unsigned char data);         // Port 0xBF/0xBD written.
        unsigned char readStatusFlag();                 // Port 0xBF/0xBD read.
        void reset();                                   // reset VDP.
        void dumpVRAM(unsigned int, int nb_lines);      // Dump VDP VRAM.
        void dumpCRAM();                                // Dump VDP CRAM.
        void update(unsigned int *s, bool drawline);    // Update VDP.
        unsigned short getVRAMAddr();		            // Get VDP pointer.
        bool getIrqLinePending() {return irq_line_pending;}
        unsigned int   line_buffer [256];              // Line buffer for tile/sprite priority.
        unsigned char  tile_mask   [256];              // Pixels above sprites are marked here.
        unsigned char  spr_col     [256];              // Use for sprite collision.
        unsigned int   *colors;                        // For on fly color conversion.
        unsigned char  *VRAM;                          // Video memory.
        unsigned char  *CRAM;                          // Color RAM.
        unsigned short map_addr;                       // Where in vram is tilemap.
        unsigned short sit_addr;                       // for sprite info. table.
        unsigned char  regs[VDP_REGISTER_NBR];         // VDP Registers.
        unsigned char  vdp_status;                     // used with portBF read.
        unsigned char  v_counter;                      // Vertical scanline ctr.
        unsigned char *v_cnt;		           		   // point ntsc/pal vcount values.
        int line;                                      // Line actually drawn.
        unsigned char     i_counter;                   // Interrupt Line counter.
        unsigned char  rd_data_port_buffer;		   	   // Buffer used in read data port.
        bool irq_line_pending;
        bool vsynch_irq_pending;
        bool irqAsserted(){return sms_irq;}
        bool irq_accepted;

        /* Implemetntation of ImplementsSaveState. */
        bool saveState( ofstream &ofs);
        bool loadState( ifstream &ifs);
		void setNTSC(bool);	
		
    protected:

        unsigned char  latch;                          	// Latch for address.
        unsigned short addr;                           	// VDP address pointer.
        unsigned char  cmd_type;			   			// VRAM Wr/Rd, VDP Wr Reg or CRAM Wr.
        bool           cmd_flag;                       	// Flag for 2 bytes cmd.
        unsigned char r_col[4];			   				// Precalc Red possible values.
        unsigned char g_col[4];			   				// Precalc Green possible values.
        unsigned char b_col[4];			   				// Precalc Blue possible values.

        void updateIRQAssertion();
        void writeRegs(unsigned char r,unsigned char v);        // Called on write regs.
        virtual void traceBackGroundLine(unsigned int *s);	    // Draw one line.
        void displaySpritesLine();                              // Used in traceBackGroundLine.
        unsigned int colorSMS8BitsToColor32Bits(unsigned char c); // Color convertor Helper.
        unsigned int colorGG12BitsToColor32Bits(unsigned short data);

    private:
        bool sms_irq;                                  	// Set when VDP gen. an irq.
        Z80 *cpu;
};
#endif
