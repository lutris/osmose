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
 * File: IOMapper_GG.h
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
#ifndef IO_MAPPER_GG_H
#define IO_MAPPER_GG_H

#include "IOMapper.h"

using namespace std;

class IOMapper_GG : public IOMapper
{
    public:

        IOMapper_GG(VDP &, SN76489 &);		// Constructor.
        virtual ~IOMapper_GG() {};
        void reset();
        unsigned char in8(unsigned  address);
        void out8(unsigned  address, unsigned  char data);

    private:

};
#endif
