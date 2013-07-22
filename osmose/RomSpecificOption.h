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
 * File: RomSpecificOption.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class will store ROM CRC32 and specific options for
 * rom that need them to run.
 *
 * Author: Vedder Bruno
 * Date: 22.11.2006 13:08:54
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef ROM_SPECIFIC_OPTION_H
#define ROM_SPECIFIC_OPTION_H
#include "Options.h"
#include <iostream>
#include "QLogWindow.h"

enum
{
    CODE_MASTER_MAPPER 	= 0x1,
    KOREAN_MAPPER		= 0x2,
    VIDEO_PAL			= 0x4,
    INTERRUPT_HACK	   	= 0x8,
    SPORT_PADDLE_INPUT  = 0x10,
    JAPANESE_MACHINE    = 0x20
};

/* Entry into our database. */
typedef struct
{
    unsigned int crc32;
    unsigned int specific_options;
} RSO_DB_Entry;

class SpecificRomOptionDatabase
{
    public:

        static unsigned int getOptions(unsigned int rom_crc32, Options *o);

    private:

        /* Private Constructor. This class is never instanciated. */
        SpecificRomOptionDatabase();
        static const RSO_DB_Entry db[];
};


#endif
