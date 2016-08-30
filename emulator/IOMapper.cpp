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
 * File: IOMapper.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle emulator input/output operation.
 *
 * Author: Vedder Bruno
 * Date: 08/10/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "IOMapper.h"
#include "Bits.h"

/* Constructor need VDP reference */
IOMapper::IOMapper(VDP & v, SN76489 & p) : vdp( v ), psg( p )
{
    reset();
}

/*----------------------------------------------------------------------*/
/* This method resets ports.						*/
/*----------------------------------------------------------------------*/
void IOMapper::reset()
{
    if (opt.inputType == DEFAULT_PAD)
    {
        port3F = 0xFF;	// Active low
    }
    else
        if	 (opt.inputType == PADDLE)
        {
            port3F = 0x30;	// 00110000b
        }
    port3E = 0xA4;
    portPAD1 = 0xFF;
    portPAD2 = 0xFF;
    paddleValue = 0;
    flipFlop = false;
}


/*----------------------------------------------------------------------*/
/* Based on Charles MacDonald documentation, this method dispatches	*/
/* port write, depending on A7, A6 and A0 address line.			*/
/*----------------------------------------------------------------------*/
void IOMapper::out8(unsigned port, unsigned char value)
{
    if (port <= 0x3F)
    {
        if (port & BIT0)  // Write to port 3F
        {
#ifdef AUTO_NAT_VERBOSE
            cout << "AUTO_NAT port 0x3F written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif

            port3F = value;
            if ( (port3F & BIT0) && (port3F & BIT2) )
            {
#ifdef AUTO_NAT_VERBOSE
                cout << "Auto nationalisation asked." << endl;
#endif
                if (opt.WorldVersion == EXPORT)
                {
                    // Copy 3F bit7 to DD bit7
                    if (port3F & BIT7)
                    {
                        portPAD2 |= BIT7;
                    }
                    else
                    {
                        portPAD2 &= (0x7F);
                    }
                    // Copy 3F bit5 to DD bit6
                    if (port3F & BIT5)
                    {
                        portPAD2 |= BIT6;
                    }
                    else
                    {
                        portPAD2 &= 0xBF;
                    }
                }
                else
                {
                    portPAD2 &= 0x3F;
                }

                if ( ((value & BIT0) && (value & BIT2))== 0 )
                {
#ifdef AUTO_NAT_VERBOSE
                    cout << "Auto nationalisation reset asked." << endl;
#endif
                }
            }
            if (port3F & BIT5)
            {
                // cout << "Selecting X7-X4 value on DC" << endl;
            }
            else
            {
                // cout << "Selecting X3-X0 value on DC" << endl;
            }
            return;
        }
        else  // Write to port 3E
        {
#ifdef MEM_CTRL_VERBOSE
            cout << "MEM CTRL port 0x3E written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif
            port3E = value;
#ifdef MEM_CTRL_VERBOSE
            if (value & BIT2)
            {
                cout << "I/O chip Disable." << endl;
            }
            else
            {
                cout << "I/O chip Enabled." << endl;
            }

            if (value & BIT3)
            {
                cout << "BIOS ROM Disable." << endl;
            }
            else
            {
                cout << "BIOS ROM Enabled." << endl;
            }

            if (value & BIT4)
            {
                cout << "Work Ram Disable (For battery backed RAM ?)." << endl;
            }
            else
            {
                cout << "Work Ram Enable." << endl;
            }

            if (value & BIT5)
            {
                cout << "Card slot Disable." << endl;
            }
            else
            {
                cout << "Card slot Enable." << endl;
            }

            if (value & BIT6)
            {
                cout << "Cartridge slot Disable." << endl;
            }
            else
            {
                cout << "Cartridge slot Enable." << endl;
            }
            if (value & BIT7)
            {
                cout << "Expansion slot Disable." << endl;
            }
            else
            {
                cout << "Expansion slot Enable." << endl;
            }
#endif
            return;
        }
    }

    if (port <= 0x7F)
    {
        psg.writePort(value);
        return;
#ifdef PSG_VERBOSE
        cout << "PSG port 0x7F written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif
        return;
    }

    if (port <= 0xBF)
    {
        if (port & BIT0) // Write on VDP Ctrl Port 0xBF
        {
#ifdef VDP_ACCESS
            cout << "VDP_CTRL port 0xBF written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif
            vdp.writeCtrlPort( value );
            return;
        }
        else		// Write on VDP Data Port 0xBE
        {
#ifdef VDP_VERBOSE
            cout << "VDP_DATA port 0xBE written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif
            vdp.writeDataPort( value );
            return;
        }
    }
#ifdef VDP_VERBOSE
    cout << "Unknown port "<< hex << setw(2) << setfill('0') << (int)port << " written with value " << hex << setw(2) << setfill('0') << (int)value << endl;
#endif

}

/*----------------------------------------------------------------------*/
/* Based on Charles MacDonald documentation, this method dispatches	*/
/* port read, depending on A7, A6 and A0 address line.			*/
/*----------------------------------------------------------------------*/
unsigned char IOMapper::in8(unsigned port)
{
    if (port == 0x3E)
    {
        return port3E;
        //cout << "MEM CTRL Port 0x3E: Read, value is " << hex << setw(2) << setfill('0') << (int)port3E << endl;
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
//#ifdef VDP_VERBOSE
            cout << "NOT IMPLEMENTED: VDP port H COUNTER 0x7F read."<< endl;
//#endif
            return 0xFF;
        }
        else 			// Read on VDP Vertical counter
        {
#ifdef VDP_VERBOSE
            cout << "VDP, port V COUNTER 0x7E read."<< endl;
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
    cout << "Unknown port "<< hex << setw(2) << setfill('0') << (int)port << " read."<< endl;
}
