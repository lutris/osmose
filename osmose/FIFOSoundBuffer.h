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
 * File: FIFOSoundBuffer.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class define Circular sound buffer utility.
 *
 * Author: Vedder Bruno
 * Date: 12/07/2006, 20h00 Chile, 'Detroit de Magellan'
 *
 * URL: http://bcz.asterope.fr
 */
#ifndef FIFO_SOUND_BUFFER_H
#define FIFO_SOUND_BUFFER_H
#include "BasicTypes.h"


class FIFOSoundBuffer
{
    public:
        /* Constructor. */
        FIFOSoundBuffer(u32 size);

        /* Destructor. */
        ~FIFOSoundBuffer()
        {
            delete data_;
        }

        /* Write a value if buffer is not full. */
        bool write(s16 value);

        /* read a single value if available. */
        inline s16 read();

        /* Read multiple values. */
        void read(s16 *, u32 nbr);

        /* Return true if at least one sample is available. */
        bool dataAvailable()
        {
            return (total_generated_ > total_played_);
        }

        /* return true is there is space for more sample. */
        bool spaceAvailable()
        {
            return (total_generated_ - total_played_ < data_size_);
        }

        u32 numberDataAvailable()
        {
            return total_generated_ - total_played_;
        }

        /* Reset the FIFO. */
        void reset();

    private:
        u32 data_size_;  /* Size of the circular buffer. */
        s16 *data_; /* Pointer to our buffer. */
        u32 generated_index_;
        u32 played_index_;
        u32 total_generated_;
        u32 total_played_;
};

#endif
