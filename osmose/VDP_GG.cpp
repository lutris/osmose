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
 * File: VDP_GG.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle GAMEGEAR's VDP (Video Display Processor)operation.
 *
 * Author: Vedder Bruno
 * Date: 25/10/2006, 19h15
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "VDP_GG.h"

static unsigned color_latch = 0;

/*----------------------------------------------------------------------*/
/* VDP_GG Constructor.                                                  */
/*----------------------------------------------------------------------*/
VDP_GG::VDP_GG(Z80 *c, bool ntsc) : VDP( c, ntsc )
{
}

/*----------------------------------------------------------------------*/
/* This method handles write operation on the GAMEGEAR VDP data port.   */
/*----------------------------------------------------------------------*/
void VDP_GG::writeDataPort(unsigned char data)        /* Port 0xBE written            */
{
    cmd_flag = false;

    rd_data_port_buffer = data; // CMD docs says that write, load buffer with it's value.

    // destination is VRAM or CRAM ?
    if (cmd_type == 3)
    {
        if (!(addr & 0x1))
        {
            color_latch = data;
        }
        else
        {
            //CRAM[addr & 0x3F] = data; // data not anded with 1f. It's done with rgb rate.
            unsigned short col = ((data & 0xF) <<8) | color_latch;
            unsigned short *cram_w = (unsigned short*) &CRAM[addr & 0x3e];
            *cram_w = col;
            colors[(addr>>1) & 0x1f] = colorGG12BitsToColor32Bits( col );
        }
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

/*--------------------------------------------------------------*/
/* This method draws a scanline.                                */
/*                                                              */
/* Drawing is done in two pass:                                 */
/*         - Render tile background                             */
/*        (sprite are rendered, then)                           */
/*      - Render tile that cover sprites                        */
/*--------------------------------------------------------------*/
void VDP_GG::traceBackGroundLine(unsigned int *s)
{
    unsigned int   c,pos;
    unsigned int *dst;
    unsigned int *scr;
    unsigned short currentTile;
    unsigned char  i, o, x, y, col_index, attrib;
    int current_line;
    unsigned int   p;

    // scr ptr in our SDL_Surface points line to be drawn.
    scr = (unsigned int*) s + (256 * line);

    /* Fill the undrawn  lines with  00.*/
    if ((line<24) || (line>167))
    {
        memset(scr, 0x0, 0x400);
        return;
    }

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

        /* Draw a blank line directly in screen if display is disabled. */
        if (!(REG1 & BIT6))
        {
            memset(scr,0x00, 0x400); // 0x400 means 256 32bits pixels.
            return;
        }


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

    // Copy Partial buffer_line in screen line:
    memcpy(scr+48,dst+48, 640);
}
