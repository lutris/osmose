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
 * File: DebugEventThrower.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This interface declares behaviour for a thrower of debug events.
 * It's done to help debugging SMS/GG hardware and Osmose code.
 *
 * Author: Vedder Bruno
 *
 * Date: 16.11.2006 10:42:28
 *
 * URL: http://bcz.asterope.fr/
 */
 
#include "DebugEventThrower.h"

void DebugEventThrower::attachDebugEventListener(DebugEventListener *el)
{
    del = el;
}

void DebugEventThrower::throwDebugEvent(int type,char *source, char *msg)
{
    if (del != NULL)
    {
        del->sendDebugEvent(type, source, msg);
    }
    else
    {
        cerr << "Trying to throw DebugEvent but the Thrower is not attached to the listener !" << endl;
    }
}






