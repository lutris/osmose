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
 * File: SaveState.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class provide an interface for Savestate.
 *
 * Author: Vedder Bruno
 * Date: 27.11.2006 10:31:16
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef SAVESTATE_H
#define SAVESTATE_H

#include <fstream>
#include <iostream>
#include <iomanip>

#include "BasicTypes.h"

using namespace std;

class ImplementsSaveState
{
    public:
        virtual bool saveState(ofstream &ofs) = 0;
        virtual bool loadState(ifstream &ifs) = 0;
        virtual ~ImplementsSaveState() {};
};

#endif
