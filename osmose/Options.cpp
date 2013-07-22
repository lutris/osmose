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
 * File: Options.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This file contains resets function for Options, and
 * emulator options. It's nothing else than default values.
 *
 * Author: Vedder Bruno
 * Date: 11/01/2005, 18h40
 *
 * URL: http://bcz.asterope.fr
 *****************************************************************************/
#include "Options.h"
#include "MemoryMapper.h"
#include <cstring>

// Global emulator options instance.
Options opt; 
EmulatorOptions      emu_opt; 

void Options::reset()
{
    // Setup defaut machine options.
    WorldVersion = true;		            // Not japanese sms, Export machine.
    MachineType = SMS;                     	// Default Machine Type.
    inputType = DEFAULT_PAD;	            // Default PAD instead SPORT PAD.
    acceleration = DEFAULT_ACCELERATION;	// Default Paddle acceleration.
    ntsc = true;		                	// Default NTSC video timing.
    mapperType = SegaMapper;		        // No codemaster mapper.
    irq_hack = false;
    videoFilter = NEAREST;
}

void EmulatorOptions::reset()
{
    // Setup defaut emulator options.
    fullscreen_flag   = false;
    sound             = true;
    bright_palette    = true;
    default_config    = true;
    display_fps       = false;
    tracejoy		  = false;
    memset(ini_file,0,512);
}
