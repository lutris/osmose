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
 * Description: This class will handle GAMEGEAR's VDP (Video Display Processor)operation.
 *
 * Author: Vedder Bruno
 * Date: 25/10/2006, 19h15
 *
 * URL: http://bcz.asterope.fr/
 */
 
#ifndef VDP_GG_H
#define VDP_GG_H

#include "VDP.h"

class VDP_GG : public VDP
{
    public:
        VDP_GG(Z80 *c, bool ntsc);
        void writeDataPort(unsigned char data);
        void traceBackGroundLine(unsigned int *s);
};

#endif
