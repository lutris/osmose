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
 * File: VDP.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle VDP (Video Display Processor)operation.
 *
 * Author: Vedder Bruno
 * Date: 11/10/2004, 08h30
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "VDP.h"

extern Options opt;

// Pre calculated Vertical count values, for 192 line NTSC video.
unsigned char vcount_ntsc_192[262] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
    0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9,
    0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9,
    0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

// Pre calculated Vertical count values, for 192 line pal/secam video.
unsigned char vcount_palsecam_192[313] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,
    0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
    0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
    0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
    0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

/* Constructor */
VDP::VDP(Z80 *c, bool ntsc)
{
    cpu = c;
    VRAM   = new unsigned char[0x4000];
    CRAM   = new unsigned char[64];
    colors = new unsigned int[64];

    // Select appropriate vcount array, depending on ntsc/pal option.
    if (ntsc == true)
    {
        v_cnt = vcount_ntsc_192;
    }
    else
    {
        v_cnt = vcount_palsecam_192;
    }

    if ((VRAM !=NULL) && (CRAM !=NULL))
    {
        for (int i=0; i < 64; i++)
        {
            CRAM[i] = 0x0;
        }
        for (int i=0; i < 0x4000; i++)
        {
            VRAM[i] = 0x0;
        }
        reset();
    }
    else
    {
        cerr << RED("Unable to allocate memory for ROM banks !") << endl;
        cerr << RED("Exiting.") << endl;
        ::exit(-1);
    }
}


/*-------------------------------------------------------------*/
/* This method handles write operation on the VDP data port.   */
/*-------------------------------------------------------------*/
void VDP::writeDataPort(unsigned char data)        /* Port 0xBE written            */
{
    cmd_flag = false;

    rd_data_port_buffer = data; // CMD docs says that write, load buffer with it's value.

    // destination is VRAM or CRAM ?
    if (cmd_type == 3)
    {
        CRAM[addr & 0x1F] = data; // data not anded with 1f. It's done with rgb rate.
#ifdef VDP_VERBOSE
        cout << "CRAM written: at 0x" << hex << setw(4) << setfill('0')<< addr << " with value "<< setw(2) << setfill('0') << (int)data <<endl;
#endif
        colors[addr & 0x1f] = colorSMS8BitsToColor32Bits(data);
        addr++;
        addr &=0x3FFF;

    }
    else  // Destination is VRAM
    {
        VRAM[addr] = data;

#ifdef VDP_VERBOSE
        cout << "VRAM written: at 0x" << hex << setw(4) << setfill('0')<< addr << " with value "<< setw(2) << setfill('0') <<(int)data <<endl;
#endif
        addr++;
        addr &=0x3FFF;
    }
}

/*---------------------------------------------------------------*/
/* This method convert 8bit xxRRGGBB to the 32 bits :			 */
/* 11111111BBBBBBBGGGGGGGGRRRRRRRR colors .						 */
/*---------------------------------------------------------------*/
unsigned int VDP::colorSMS8BitsToColor32Bits(unsigned char data)
{
    unsigned int r, g, b, out;

    r = r_col[(data & 3)];
    g = g_col[(data >> 2) &3];
    b = b_col[(data >> 4) &3];
	out = (unsigned int) (0xFF000000 | (b << 16) | (g << 8) | r);
    return out; 
}

/*---------------------------------------------------------------*/
/* This method convert 12bit xxxxRRRRGGGGBBBB to 32 bits		 */
/* 11111111BBBBBBBGGGGGGGGRRRRRRRR colors .						 */
/*---------------------------------------------------------------*/
unsigned int VDP::colorGG12BitsToColor32Bits(unsigned short data)
{
    unsigned char r, g, b;

    r = (data & 0xF) << 4;
    g = ((data >> 4) & 0xF)<<4;
    b = ((data >> 8) & 0xF)<<4;

    return (unsigned int)(b << 16) | (g <<8) | (r);
}

/*-------------------------------------------------------------*/
/* This method handles read operation on the VDP data port.    */
/*-------------------------------------------------------------*/
unsigned char VDP::readDataPort()                /* Port 0xBE read             */
{
    unsigned char r;

    cmd_flag = false;
    r = rd_data_port_buffer;
#ifdef VDP_VERBOSE
    cout << "VRAM read: at 0x" << hex << setw(4) << setfill('0')<< addr << " value = "<< setw(2) << setfill('0') <<(int)r <<endl;
#endif
    rd_data_port_buffer = VRAM[addr];
    addr++;
    addr &= 0x3FFF;
    return r;
}

/*-------------------------------------------------------------*/
/* This method handles write operation on the VDP control port.*/
/* This port is at 0xBF                                               */
/*-------------------------------------------------------------*/
void VDP::writeCtrlPort(unsigned char data)        /* Port 0xBF/0xBD written   */
{
    if (cmd_flag == false)
    {
        cmd_flag = true;          /* We receive first byte of command word  */
        latch = data;
    }
    else
    {
        cmd_flag = false;        /* We receive second byte of command word  */
        cmd_type = data >> 6;    /* 2second byte MSB are cmd type            */
        addr = ( (data & 0x3F ) << 8) | latch;
        if (cmd_type == 0)
        {
            rd_data_port_buffer = VRAM[addr];
            addr = (addr +1) & 0x3FFF;

        }

        if (cmd_type == 2)  // Cmd: 10 VDP register write */
        {
            writeRegs(data & 0xF, latch);
        }

#ifdef VDP_VERBOSE
        switch (cmd_type)
        {
            case 0:
                cout << "VRAM read: VDP Addr set to 0x" << hex << setw(4) << setfill('0')<< addr << endl;
                break;
            case 1:
                cout << "VRAM write: VDP Addr set to 0x" << hex << setw(4) << setfill('0')<< addr << endl;
                break;
            case 2:
                cout << "REG write: VDP Regs " << (int)(data & 0xF) << " written with value "<< hex << setw(2) << setfill('0')<<(int)latch << endl;
                break;
            case 3:
                cout << "CRAM write: Addr in palete is " << hex << setw(4) << setfill('0')<<(int)addr << endl;
                break;
        }
#endif
    }
}


/*------------------------------------------------------------*/
/* Call back when port BF/BD is read.                               */
/*------------------------------------------------------------*/
unsigned char VDP::readStatusFlag()
{
    unsigned char tmp;

    cmd_flag = false;   // this flag is cleared when Ctrl port is read.
    tmp = vdp_status;
    vdp_status &= 0x1f; // Clear bit 6 & 7 from vdp_status.
    irq_line_pending = false;
    vsynch_irq_pending = false;
    updateIRQAssertion();
    return tmp;
}

/*------------------------------------------------------------*/
/* This method return VDP RAM internal pointer.               */
/*------------------------------------------------------------*/
unsigned short VDP::getVRAMAddr()
{
    return addr;
}



/*------------------------------------------------------------*/
/* This method will reset the VDP by setting latch / regs     */
/* to Zero, supposing it's the thing to do !                      */
/*------------------------------------------------------------*/
void VDP::reset()
{
    addr      = 0;
    latch     = 0;
    cmd_flag  = false;
    v_counter = 0;
    i_counter = 0xFF;
    vdp_status= 0x1f; // 00011111b
    line      = 0;
    sms_irq   = false;
    irq_line_pending = false;
    vsynch_irq_pending = false;
    cmd_type  = 0;
    rd_data_port_buffer = 0;

    if (emu_opt.bright_palette == true)
    {
       /* r_col[0] = 0;
        r_col[1] = 10;
        r_col[2] = 21;
        r_col[3] = 31;

        g_col[0] = 0;
        g_col[1] = 21;
        g_col[2] = 42;
        g_col[3] = 63;

        b_col[0] = 0;
        b_col[1] = 10;
        b_col[2] = 21;
        b_col[3] = 31;
*/
		r_col[0] = 0x00;
        r_col[1] = 0x55;
        r_col[2] = 0xAA;
        r_col[3] = 0xFF;

		g_col[0] = 0x00;
        g_col[1] = 0x55;
        g_col[2] = 0xAA;
        g_col[3] = 0xFF;

		b_col[0] = 0x00;
        b_col[1] = 0x55;
        b_col[2] = 0xAA;
        b_col[3] = 0xFF;

    }
    else
    {
/*
        r_col[0] = 0;
        r_col[1] = 8;
        r_col[2] = 16;
        r_col[3] = 24;

        g_col[0] = 0;
        g_col[1] = 16;
        g_col[2] = 32;
        g_col[3] = 48;

        b_col[0] = 0;
        b_col[1] = 8;
        b_col[2] = 16;
        b_col[3] = 24;
*/
		r_col[0] = 0x00;
        r_col[1] = 0x55;
        r_col[2] = 0xAA;
        r_col[3] = 0xFF;

		g_col[0] = 0x00;
        g_col[1] = 0x55;
        g_col[2] = 0xAA;
        g_col[3] = 0xFF;

		b_col[0] = 0x00;
        b_col[1] = 0x55;
        b_col[2] = 0xAA;
        b_col[3] = 0xFF;
  
  }

    for (int i=0; i<VDP_REGISTER_NBR; i++)
    {
        regs[i] = 0;
    }

    REG2 = 0xE;         /* xxxx111x -> map default to 0x3800 in VRAM */
    map_addr = 0x3800;  /* REG2 converted into VRAM address.             */

    REG5 = 0x7E;         /* x111111x -> sit default to 0x3F00 in VRAM */
    sit_addr = 0x3F00;  /* REG5 converted into VRAM address.             */

    REG10 = 0xFF;        /* No Line Interrupt */
#ifdef BUILT_IN_DEBUGGER
    irq_accepted = false;
#endif
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function.                       */
/* Note that this method will dump VDP VRAM.                      */
/*------------------------------------------------------------*/
void VDP::dumpVRAM(unsigned int sa, int nb_lines)
{
    cout << "Dumping VDP RAM:"<<endl;

    sa &=0x3fff;
    for (int i=0; i<nb_lines; i++)
    {
        cout << hex << setw(4) << setfill('0') << (i*16+sa)  << ": ";
        for (int o=0;o<16;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) VRAM[sa++] << " ";
            sa &= 0x3FFF;
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function.                       */
/* Note that this method will dump VDP CRAM.                      */
/*------------------------------------------------------------*/
void VDP::dumpCRAM()
{
    int ind = 0;
    cout << "Dumping VDP CRAM:"<< endl;
    for (int i=0; i<4; i++)
    {
        cout << hex << setw(4) << setfill('0') << (i*16)  << ": ";
        for (int o=0;o<16;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) CRAM[ind++] << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This method is called on each VDP register write. Parameter*/
/* is the index of the register in reg array.                      */
/*------------------------------------------------------------*/
void VDP::writeRegs(unsigned char r,unsigned char v)
{
    regs[r] = v;

    switch (r)
    {
        case 0:
            /* Change IRQ assertion if Line IRQ are enabled/disabled.*/
            updateIRQAssertion();
            break;
        case 1:
            /* Change IRQ assertion if VSYNC IRQ are enabled/disabled.*/
            updateIRQAssertion();
            break;
        case 2:
            map_addr = (REG2 & 0xE) << 10; /* 0xE = 00001110b. */
            break;
        case 5:
            sit_addr = (((REG5 >> 1) & 0x3F) << 8 );
            break;
    }

#ifdef VDP_VERBOSE
    if (r == 2 || r==5)
    {
        cout << "VDP REGISTER: tile map address set to 0x" << hex << setw(4) << setfill('0') << map_addr << endl;
        cout << "VDP REGISTER: sprite information table set to 0x" << hex << setw(4) << setfill('0') << sit_addr << endl;
    }
#endif
}

/*------------------------------------------------------------*/
/* This method is called when a scanline has been drawn.      */
/* It draws one line in screen. Set sms_irq if VDP triggers   */
/* an interrupt.                                              */
/* If drawline is true, line render is done else it's skipped */
/* This is for frame skip, to handle interrupt system, but to */
/* avoid drawing line if frame is not displayed.              */
/*------------------------------------------------------------*/
void VDP::update(unsigned int *s, bool drawline)
{
    if (line < 0xC0)
    {
        if (drawline == true)
        {
            traceBackGroundLine(s);
        }
    }

    /* V-Blank interrupt. */
    if (line == 0xC1)
    {
        vdp_status |= BIT7;
        vsynch_irq_pending = true;
    }

    /* Line interrupt. */
    if (line < 193)
    {
        i_counter--;
        /* Line counter overflow. */
        if (i_counter == 0xFF)
        {
            i_counter = REG10;
            irq_line_pending = true;
        }
    }
    else i_counter = REG10;

    updateIRQAssertion();
    v_counter = v_cnt[line];
#ifdef BUILT_IN_DEBUGGER
    /*
    	This event is thrown on every scanline. The dedbugger will react depending
    	on the scanline break point.
    */
    throwDebugEvent(DbgEvtScanlineBreakpoint,"VDP", "End of current Scanline.");
#endif
}

/*------------------------------------------------------------*/
/* This method update sms_irq value depending on VDP registers*/
/* and interrupt pending.									  */
/*------------------------------------------------------------*/
void VDP::updateIRQAssertion()
{
    sms_irq = false;
    if (irq_line_pending && (REG0 & BIT4))
    {
        sms_irq = true;
        //cout << "IRQ from Line IRQ " << dec <<line << endl;
    }
    if (vsynch_irq_pending && (REG1 & BIT5))
    {
        sms_irq = true;
        //cout << "IRQ from Line VSYNCH " << dec <<line << endl;
    }
    if (sms_irq)
    {
        if (opt.irq_hack) cpu->step();
        cpu->interrupt( 0xFF );
    }
}

/*--------------------------------------------------------------*/
/* This method draws a scanline.                                */
/*                                                              */
/* Drawing is done in two pass:                                 */
/*         - Render tile background                             */
/*        (sprite are rendered, then)                           */
/*      - Render tile that cover sprites                        */
/*--------------------------------------------------------------*/
void VDP::traceBackGroundLine(unsigned int *s)
{
    unsigned int   c,pos;
    unsigned int *dst;
    unsigned int *scr;
    unsigned short currentTile;
    unsigned char  i, o, x, y, col_index, attrib;
    int current_line;
    unsigned int   p;

    /* scr ptr in our SDL_Surface points line to be drawn. */
    scr = (unsigned int*) s + (256 * line);

    /* Draw a blank line directly in screen if display is disabled. */
    if (!(REG1 & BIT6))
    {
        memset(scr,0x0, 0x400); // 0x200 means 256 32bits pixels.
        return;
    }


    /* Our destination is one 256 pixel line. */
    dst = line_buffer;

    /* Clear our tileMask. */
    memset(tile_mask,0x00, 0x100);

    /*
    	 Note that x is never tested for >255 since it automaticaly wraps
    	 due to it's unsigned char declaration.
    */

    /* Now, for 32 tiles... */
    for (o=0; o<32;o++)
    {
        /* x = X scroll register, y = Y scroll register. */
        y = REG9;
        x = REG8;

        /* Top 2 rows of screen not affected by horizontal scrolling. */
        if ((REG0 & BIT6) && (line<=15))
        {
            x = 0;
        }

        x += o *8;

        /* current_line = current line + scroll register modulated to stay in screen. 192 could be OK. */
        if ((o >= 24) && (REG0 & BIT7))
        {
            /* Disable vertical scrolling for columns 24-31 */
            current_line = ((line) % 224);
        }
        else
        {
            current_line = ((line+y) % 224);
        }

        /*
        	Now get VRAM index of the Tile/attrib in VDP memory.
        	8x8 Tile at Coord x, y = (x*64) + (y /8)
        	x * 64 because a line is 32 tiles, with 2 bytes for tile index and attribute.
        	y /8 because a tile is made of 8 lines.
        */
        pos = ((current_line>>3)<<6) + o * 2;

        /* get it's tile Index. */
        currentTile = VRAM[ map_addr + pos++];

        /* get it's attribute. */
        attrib      = VRAM[ map_addr + pos++];

        if (attrib & BIT0)
        {
            currentTile |=0x100;        // 9th tile index bit.
        }

        //    line in tile converted to VRAM ind
        if (attrib & BIT2)
        {
            // Verticaly flipped tile.
            c = ((7 - (current_line & 7))<<2) + (currentTile<<5);
        }
        else
        {
            c = ((current_line & 7)<<2) + (currentTile<<5);
        }

        // Four bytes are read into one 32bits variable. This avoid 3 memory access.
        // Bits plan are like this in the variable (intel architecture):
        // P3P2P1P0 which is inverse order or ram content. This is due to intel
        // endianness
        unsigned int *cst = (unsigned int *) &VRAM[c];
        p = *cst;
        
        // Patch for PowerPC indianess.
        //p = (p >> 24) | ((p & 0x00FF0000) >> 8) | ((p & 0x0000FF00)<< 8) | (( p &0xFF)<<24);
        c += 4;

        // Draw 8 horizontals pixels.
        switch ((attrib>>1) & 3)
        {
            case 0: // Tile not flipped
                for ( i = 0; i<8; i++)
                {
                    col_index = ((p >>7)&1) | (((p >> 15)<<1)&2) | (((p >> 23)<<2)&4) | ((p >> 31)<<3);
                    if (attrib & BIT3) col_index|=0x10; // Then use sprite palete
                    dst[x] = colors[col_index];
                    if ((attrib & BIT4) && (col_index != 0x10) && (col_index !=0x0))
                    {
                        tile_mask[x] = 1;
                    }
                    x++;
                    p<<=1;
                }
                break;

            case 1: // Tile flipped on x
                for ( i = 0; i<8; i++)
                {
                    col_index = (p&1) | ((p>>8) & 1)<<1 | ((p>>16) & 1 )<<2 | ((p >>24) &1)<<3;
                    if (attrib & BIT3) col_index|=0x10; // Then use sprite palete
                    dst[x] = colors[col_index];
                    if ((attrib & BIT4) && (col_index != 0x10) && (col_index !=0x0))
                    {
                        tile_mask[x] = 1;
                    }
                    x++;
                    p>>=1;
                }
                break;

            case 2: // Tile flipped on y
                for (int i=0; i<8;i++)
                {
                    col_index = ((p>>7) &1)| ((p >> 15)&1)<<1 | ((p >> 23)&1)<<2 | ((p >> 31)&1)<<3;
                    if (attrib & BIT3) col_index|=0x10; // Then use sprite palete
                    dst[x] = colors[col_index];
                    if ((attrib & BIT4) && (col_index != 0x10) && (col_index !=0x0))
                    {
                        tile_mask[x] = 1;
                    }
                    x++;
                    p<<=1;
                }
                break;

            case 3: // Tile flipped on x and y
                for (int i=0; i<8;i++)
                {
                    col_index = (p & 1) | ((p>>8) & 1)<<1 | ((p>>16) & 1)<<2 | ((p>>24) & 1)<<3;
                    if (attrib & BIT3) col_index|=0x10; // Then use sprite palete
                    dst[x] = colors[col_index];
                    if ((attrib & BIT4) && (col_index != 0x10) && (col_index !=0x0))
                    {
                        tile_mask[x] = 1;
                    }
                    x++;
                    p>>=1;
                }
                break;
        } // switch attrib flip x/y
    }
#ifdef DISPLAY_SPRITES
    displaySpritesLine();
#endif
    if (REG0 & BIT5) // Do not display (clear) leftmost column of the screen
    {
        unsigned short c = colors[(REG7 & 0xF)+16];
        for (int u=0; u < 8; u++)
        {
            dst[u] = c;
        }
    }

    // Copy buffer_line in screen line:
    memcpy(scr,dst, 1024);

}

/*-------------------------------------------------------------*/
/* This method selects VDP timings vcounts.					   */
/*-------------------------------------------------------------*/
void VDP::setNTSC(bool t)
{
    // Select appropriate vcount array, depending on ntsc/pal option.
    if (t == true)
    {
        v_cnt = vcount_ntsc_192;
    }
    else
    {
        v_cnt = vcount_palsecam_192;
    }
}

/*-------------------------------------------------------------*/
/* This method will sprites on a given scanline on SDL_Surface */
/* The scanline is the line variable into VDP Class, which is  */
/* the current line drawn.                                     */
/*-------------------------------------------------------------*/
void VDP::displaySpritesLine()
{
    unsigned char  sprite_height = 8;
    unsigned char  displayedSprites;
    unsigned short c;
    unsigned char  col_index;
    int  y;
    unsigned int *cst;
    unsigned int p;
    bool  double_size = false;
    int x_spr[8];
    int y_spr[8];
    unsigned short ind_spr[8];
    unsigned char  line_spr[8];
    unsigned char  start_spr[8];
    unsigned char  width_spr[8];

    if (REG1 & BIT1)         // 8*16 sprites
    {
        sprite_height = 16;
    }

    displayedSprites = 0;

    /* Note that if Bit0 and Bit1 of reg1 are set, sprites are 16*32. */
    /* Earthworm jim uses this.*/
    if (REG1 & BIT0)
    {
        sprite_height  *= 2;
        double_size = true;
    }

    // For all sprite information table
    for (int j=0; j<64; j++)
    {
        y = (int)VRAM[sit_addr+j];

        // y=208 mean stop displaying sprites.
        if (y == 208)
        {
            break;
        }

        // Y position 0 means scanline 1.
        y++;
        if (y>240)
        {
            y-=256;
        }

        // Found one sprite to draw.
        if ( (line>=y) && (line<(y + sprite_height)))
        {
            if (displayedSprites == 8)
            {
                vdp_status |= BIT6; /* Sprite overflow bit */
                break;
            }

            ind_spr[displayedSprites] = VRAM[(sit_addr+129)+(j<<1)];

            if (REG6 & BIT2)        // 9th bit sprite nbr
            {
                ind_spr[displayedSprites] |= 0x100;
            }

            if (REG1 & BIT1)
            {
                ind_spr[displayedSprites] &=0x01FE;
            }


            y_spr[displayedSprites] = y;
            line_spr[displayedSprites] = line - y;
            if (double_size) 	line_spr[displayedSprites] = (line - y)>>1;
            x_spr[displayedSprites] = VRAM[(sit_addr+128)+(j<<1)];

            // Sprites moved 8 pixels left.
            start_spr[displayedSprites] = 0;                // First pixel in sprite line to draw.
            if (REG0 & BIT3)
            {
                x_spr[displayedSprites]-=8;
                if (x_spr[displayedSprites]<0)
                {
                    start_spr[displayedSprites] = -x_spr[displayedSprites];
                }
            }
            width_spr[displayedSprites] = 8;    // Nbr of pixels in sprite line to draw.
            if (x_spr[displayedSprites]>248)
            {
                width_spr[displayedSprites] = 256 - x_spr[displayedSprites];
            }
            displayedSprites++;
        }
    }

    // Draw in reverse order.
    for (int i= 0; i < 256; i++)
    {
        spr_col[i] = 0;
    }
    for (int r = displayedSprites-1; r >= 0; r--)
    {
        c = (line_spr[r]<<2) + (ind_spr[r]<<5);
        cst = (unsigned int *) &VRAM[c];
        p = *cst;
        c += 4;
        for (int i=start_spr[r]; i<width_spr[r];i++)
        {
            col_index = ((p >>7)&1) | (((p >> 15)<<1)&2) | (((p >> 23)<<2)&4) | ((p >> 31)<<3);
            col_index|=0x10; // Always use sprite palete
            if (col_index != 0x10)
            {
                if (double_size)
                {
                    if (tile_mask[x_spr[r]+i*2] == 0)
                    {
                        unsigned short u = x_spr[r]+(i*2);
                        line_buffer[u] = colors[col_index];
                        line_buffer[u+1] = colors[col_index];
                        if ((spr_col[u] == 1) || (spr_col[u+1] == 1))
                        {
                            vdp_status |= BIT5;         // Force collision to true
                        }
                        spr_col[u] = 1;
                        spr_col[u+1] = 1;
                    }
                }
                else
                {
                    if (tile_mask[x_spr[r]+i] == 0)
                    {
                        unsigned short u = x_spr[r]+i;
                        line_buffer[u] = colors[col_index];
                        if (spr_col[u] == 1)
                        {
                            vdp_status |= BIT5;         // Force collision to true
                        }
                        spr_col[u] = 1;
                    }
                }
            }
            p<<=1;
        }
    }
}

/* Implemetntation of ImplementsSaveState. */
bool VDP::saveState( ofstream &ofs)
{
    VDPSaveState vss;

    /* Fill the structure. */
    vss.map_addr = map_addr;
    vss.sit_addr = sit_addr;
    for (int i=0; i < VDP_REGISTER_NBR; i++) vss.regs[i] = regs[i];
    vss.vdp_status = vdp_status;
    vss.v_counter = v_counter;
    vss.line = line;
    vss.i_counter = i_counter;
    vss.rd_data_port_buffer = rd_data_port_buffer;
    vss.irq_line_pending = irq_line_pending;
    vss.vsynch_irq_pending = vsynch_irq_pending;
    vss.sms_irq = sms_irq;
    vss.latch = latch;
    vss.addr = addr;
    vss.cmd_type = cmd_type;
    vss.cmd_flag = cmd_flag;

    /* Save VDP data. */
    ofs.write((char *)&vss, sizeof(vss));
    if (!ofs.good()) return false;

    /* Save 16 Ko VRAM. */
    ofs.write((char *)&VRAM[0], 0x4000);
    if (!ofs.good()) return false;

    /* Save 64 bytes CRAM. */
    ofs.write((char *)&CRAM[0], 64);
    if (!ofs.good()) return false;

    return true;
}

bool VDP::loadState( ifstream &ifs)
{
    VDPSaveState vss;

    /* Load VDP data into structure */
    ifs.read((char *)&vss, sizeof(vss));
    if (!ifs.good()) return false;
    map_addr = vss.map_addr ;
    sit_addr = vss.sit_addr;
    for (int i=0; i < VDP_REGISTER_NBR; i++) regs[i] = vss.regs[i];
    vdp_status = vss.vdp_status;
    v_counter = vss.v_counter;
    line = vss.line;
    i_counter = vss.i_counter;
    rd_data_port_buffer = vss.rd_data_port_buffer;
    irq_line_pending = vss.irq_line_pending;
    vsynch_irq_pending = vss.vsynch_irq_pending;
    sms_irq = vss.sms_irq;
    latch = vss.latch;
    addr = vss.addr;
    cmd_type = vss.cmd_type;
    cmd_flag = vss.cmd_flag;

    /* Load 16 Ko VRAM. */
    ifs.read((char *)&VRAM[0], 0x4000);
    if (!ifs.good()) return false;

    /* Load 64 bytes CRAM. */
    ifs.read((char *)&CRAM[0], 64);
    if (!ifs.good())
    {
        if (ifs.eof()) cout << "EOF!" << endl;
        return false;
    }

    /* Now recompute colors that are usually computed on fly.*/
    if (opt.MachineType == SMS)
    {
        for (int i=0; i < 0x1f; i++) colors[i] = colorSMS8BitsToColor32Bits(CRAM[i]);
    }

    if (opt.MachineType == GAMEGEAR)
    {
        unsigned short *CRAM16bits = (unsigned short *) CRAM;
        for (int i=0; i < 0x1f; i++) colors[i] = colorGG12BitsToColor32Bits(CRAM16bits[i]);
    }

    return true;
}

