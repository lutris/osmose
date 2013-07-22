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
 * File: IOMapper_GG.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle GAMEGEAR emulator input/output operation.
 *
 * Author: Vedder Bruno
 * Date: 08/10/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "IOMapper_GG.h"
#include <stdlib.h>

// Constructor.
IOMapper_GG::IOMapper_GG(VDP &v, SN76489 &p) : IOMapper(v, p)
{
    reset();
}

// Reset GAMEGEAR additionnal ports.
void IOMapper_GG::reset()
{
    IOMapper::reset();
    port0x0 = 0xC0;
    port0x1 = 0x7F;
    port0x2 = 0xFF;
    port0x3 = 0x00;
    port0x4 = 0xFF;
    port0x5 = 0x00;
    port0x6 = 0xFF;
}

/*----------------------------------------------------------------------*/
/* Based on Charles MacDonald documentation, this method dispatches	*/
/* port read, depending on A7, A6 and A0 address line.			*/
/*----------------------------------------------------------------------*/
unsigned char IOMapper_GG::in8(unsigned  port)
{
    if (port == 0x0) return port0x0;
    if (port == 0x1) return port0x1;
    if (port == 0x2) return port0x2;
    if (port == 0x3) return port0x3;
    if (port == 0x4) return port0x4;
    if (port == 0x5) return port0x5;
    if (port == 0x6) return port0x6;

    if (port == 0x3E)
    {
        return port3E;
        cout << "MEM CTRL Port 0x3E: Read, value is " << hex << setw(2) << setfill('0') << (int)port3E << endl;
    }
    if (port <= 0x3F)
    {
        //cout << "NOT IMPLEMENTED / EXPERIMENTAL: Read port <=0x3f" << endl;
        return (port & 0xff);
    }

    if (port <= 0x7F)
    {
        if (port & BIT0) 	// Read H counter port.
        {
#ifdef VDP_VERBOSE
            cout << "NOT IMPLEMENTED: VDP port H COUTNER 0x7F read."<< endl;
#endif
            return 0xFF;
        }
        else 			// Read on VDP Vertical counter
        {
#ifdef VDP_VERBOSE
            cout << "VDP, port V COUTNER 0x7E read."<< endl;
#endif
            return vdp.v_counter;
        }
    }

    if (port <= 0xBF)		// Read VDP status flag
    {
        if (port & BIT0)
        {
#ifdef VDP_VERBOSE
            cout << "VDP status read."<< endl;
#endif
            return vdp.readStatusFlag();
        }
        else			// Read VDP Data port
        {
#ifdef VDP_VERBOSE
            cout << "CRAM/VRAM read."<< endl;
#endif
            return vdp.readDataPort();
        }
    }

    // Port is > 0xBF and < 0xFF
    if (port & BIT0)
    {
#ifdef PAD_VERBOSE
        cout << "Port PAD2 0xDD read."<< endl;
#endif
        return portPAD2;
    }
    else
    {
#ifdef PAD_VERBOSE
        cout << "Port PAD1 0xDC read."<< endl;
#endif
        if (opt.inputType == PADDLE)
        {
            flipFlop^=1;
            if (flipFlop == true)
            {
                portPAD1 |= BIT5;
                portPAD1 &= 0xf0;
                portPAD1 |= (paddleValue >> 4);
            }
            else
            {
                portPAD1 &= ~BIT5;
                portPAD1 &= 0xf0;
                portPAD1 |= (paddleValue & 0x0f);
            }
        }
        return portPAD1;
    }
    cout << "Unkown port "<< hex << setw(2) << setfill('0') << (int)port << " read."<< endl;
}

void IOMapper_GG::out8(unsigned  address, unsigned  char data)
{
    /* Call parent method. */
    if (address == 0)
    {
        port0x0 = data;
        return;
    }
    if (address == 1)
    {
        port0x1 = data;
        return;
    }
    if (address == 2)
    {
        port0x2 = data;
        return;
    }
    if (address == 3)
    {
        port0x3 = data;
        return;
    }
    if (address == 4)
    {
        port0x4 = data;
        return;
    }
    if (address == 5)
    {
        port0x5 = data;
        return;
    }
    IOMapper::out8( address, data);
}

