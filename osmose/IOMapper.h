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
 * File: IOMapper.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle SMS emulator input/output operation.
 *
 * Author: Vedder Bruno
 * Date: 08/10/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef IO_MAPPER_H
#define IO_MAPPER_H

#include "Definitions.h"
#include <iostream>
#include <iomanip>
#include "VDP.h"
#include "SN76489.h"
#include "Options.h"
#include "DebugEventThrower.h"

extern Options opt;

using namespace std;

class IOMapper : public DebugEventThrower
{

    protected:

        VDP     &vdp;			// Reference on VDP object.
        SN76489 &psg;			// Reference on PSG object.

    public:

        IOMapper(VDP &, SN76489 &);		// Constructor.
        virtual ~IOMapper() {};
        unsigned char paddleValue;		// Paddle knob value.
        bool flipFlop;
        unsigned char port3E;		// Memory control.
        unsigned char port3F;		// Auto nationalisation port.
        unsigned char portPAD1;		// Joypad port 1.
        unsigned char portPAD2;		// Joypad port 2.
        unsigned char WorldVersion;		// Sms type.
        virtual void reset();
        virtual void out8(unsigned address, unsigned char value);
        virtual unsigned char in8(unsigned  address);


        // These GAMEGEAR ports are here but not readable from IOMapper::in().
        // They are readable with IOMapper_GG::in()
        unsigned char port0x0;
        unsigned char port0x1;
        unsigned char port0x2;
        unsigned char port0x3;
        unsigned char port0x4;
        unsigned char port0x5;
        unsigned char port0x6;
};
#endif
