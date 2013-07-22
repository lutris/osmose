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
 
#ifndef SMS_ENVIRONMENT_H
#define SMS_ENVIRONMENT_H

#include "Definitions.h"
#include <iostream>
#include "./cpu/Z80.h"
#include "MemoryMapper.h"
#include "IOMapper.h"
#include "IOMapper_GG.h"
#include "VDP.h"


using namespace std;

class SmsEnvironment : public Z80Environment
{
    public:

        /** Constructor. */
        SmsEnvironment();

        /** Destructor. */
        virtual ~SmsEnvironment();
        virtual void disasm(u16 IP);
        virtual void onReturnFromInterrupt();
        virtual void onInterruptsEnabled();
        virtual void setMemoryMapper(MemoryMapper *m);
        virtual void setIOMapper(IOMapper *m);
        virtual void setVDP(VDP *v);
        virtual void setCPU(Z80 *c);

        // New core wrappers
        virtual u8 rd8( u16 addr );
        virtual void wr8( u16 addr, u8 value );
        virtual u8 in( u16 port );
        virtual void out( u16 port, u8 value );

        // Old Core Wrapper:
        virtual unsigned char readByte( unsigned addr )
        {
            return rd8(addr);
        };
        virtual void writeByte( unsigned addr, unsigned char data )
        {
            wr8(addr, data);
        };
        virtual void writePort( unsigned port, unsigned char data )
        {
            out(port, data);
        };
        virtual unsigned char readPort( unsigned addr )
        {
            return in(addr);
        };

    protected:

        MemoryMapper *mmapper;
        IOMapper *iomapper;
        VDP *v;
        Z80 *cpu;
};

#endif
