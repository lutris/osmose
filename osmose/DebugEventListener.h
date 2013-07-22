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
 * File: DebugEventListener.h
 *
 * Project: Osmose emulator.
 *
 * Description: This interface declares behaviour for Listening debug events.
 * It's done to help debugging SMS/GG hardware and Osmose code.
 * How it's used:
 * SmsDebugger or a logger for example implements the DebugEventListener
 * interface. The VDP, or any debugEventThrower will be attach to the
 * DebugEventListener. To throw debug event the thrower will use throwDebugEvent
 * method.
 * Author: Vedder Bruno
 *
 * Date: 16.11.2006 10:42:28
 *
 * URL: http://bcz.asterope.fr
 */
#ifndef DEBUG_EVENT_LISTENER_H
#define DEBUG_EVENT_LISTENER_H

/* Debug Event types. */
enum
{
    DbgEvtUserTrigger 			= 0,
    DbgEvtCpuStep	  			= 1,
    DbgEvtScanlineBreakpoint	= 2,
    DbgEvtCpuIrqAsserted		= 3,
    DbgEvtCpuDisableInterrupt   = 4,
    DbgEvtCpuEnableInterrupt   =  5,
    DbgEvtGeneric				= 256
};

class DebugEventListener
{
    public:

        virtual void sendDebugEvent(int event_type, char *sourcec, char *message) = 0;
        virtual ~DebugEventListener() {};
};

#endif

