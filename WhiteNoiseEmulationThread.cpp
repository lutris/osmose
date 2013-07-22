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
 *	
 * File : WhiteNoiseEmulationThread.cpp
 *
 * Description : This fake emulation thread is used to generate
 * white noise when no ROM is loaded.
 *
 * Author : B.Vedder
 *
 * Date : Sat Nov 13 11:38:27 2010
 *
 */

#include "WhiteNoiseEmulationThread.h"

/**
 * Constructor.
 */
WhiteNoiseEmulationThread::WhiteNoiseEmulationThread(QGLImage *qglimage) : EmulationThread(qglimage)
{
	setRefreshFrequency(25.0f);
}

/**
 * Destructor.
 */
WhiteNoiseEmulationThread::~WhiteNoiseEmulationThread()
{
}

/**
 * This method perform one frame emulation stuff. The videoBuffer must
 * be updated inside this method.
 */
void WhiteNoiseEmulationThread::emulateOneFrame()
{
	unsigned int col = 0;
	for (unsigned int i = 0; i < 256 * 192; i++)
	{
		int hzd = rand() & 0xFF;
		if (hzd > 0xF0)
		{
			col = rand() & 0xFF;
			col = col | (col << 8) | (col << 16) | 0xFF000000;
		}
		else
		{
			col = 0xFF000000;
		}
		videoBuffer[i] = col;
	}
}
