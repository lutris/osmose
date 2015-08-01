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
 * File: WaveWriter.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class implements waveWriter class used by Osmose for
 * saving sound. It's only designed to handle 16 bits mono 22050hz samples.
 *
 * Author: Vedder Bruno
 * Date: 25/11/2004, 14h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "WaveWriter.h"
#include <cstdlib>

/*----------------------------------------------------------------------*/
/* Constructor: Initialise structures ChunkFormat, Data Format, and	*/
/* allocate buffer of WAVE_BUFFER_SIZE for file writing. When done	*/
/* it open a file for writing and let it open, then write headers.	*/
/*----------------------------------------------------------------------*/
WaveWriter::WaveWriter(const char *filename)
{
    // Index in our sample buffer, and sample count.
    index  = 0;
    length = 0;

    // Initialise our FormatChunk structure.
    format.chunkID[0] = 'f';
    format.chunkID[1] = 'm';
    format.chunkID[2] = 't';
    format.chunkID[3] = ' ';
    format.chunkSize = 16;		// 16s bytes without chnkID/chnkSize.
    format.wFormatTag = 1;		// No compression.
    format.wChannels = 1;        	// Monophonic sound.
    format.dwSamplesPerSec = 22050;	// Sample rate.
    format.dwAvgBytesPerSec= 44100;    	// dwSamplesPerSec * wBlockAlign.
    format.wBlockAlign = 2;		// wChannels*(wBitPerSample/8).
    format.wBitsPerSample = 16;

    // Initialise our FormatChunk structure.
    data.chunkID[0] = 'd';
    data.chunkID[1] = 'a';
    data.chunkID[2] = 't';
    data.chunkID[3] = 'a';
    data.chunkSize  = 0;
    data.waveformData = (short *) NULL;

    // Allocate buffer for file writing
    data.waveformData = new  short[WAVE_BUFFER_SIZE];
    if (data.waveformData == NULL)
    {
        cerr << RED("Unable to allocate memory for waveformData.")<< endl;
        cerr << RED("Exiting.") << endl;
        exit (-1);
    }

    // Open our destination file.
    waveFile.open(filename, ios::out | ios::binary);
    if (waveFile.is_open() == true)
    {
        skip_save = false;
    }
    else
    {
        cerr << RED("Unable to open file for writing waveform data.")<< endl;
        cerr << RED("Wave file won't be saved.")<< endl;
        skip_save = true;
    }

    // Write headers.
    waveFile.write("RIFF7   WAVE", 12);
    waveFile.write((char *)&format, sizeof(FormatChunk) );
    waveFile.write((char *)&data, sizeof(DataChunk) );

}

/*----------------------------------------------------------------------*/
/* Destructor.								*/
/*----------------------------------------------------------------------*/
WaveWriter::~WaveWriter()
{
    if (data.waveformData != NULL)
    {
        delete[] data.waveformData;
    }
}

/*----------------------------------------------------------------------*/
/* This method will add data into wave sound buffer. If buffer is full  */
/* it's written to the file.						*/
/*----------------------------------------------------------------------*/
void WaveWriter::writeData(short d)
{
    if (skip_save == true)
    {
        return;
    }

    data.waveformData[index++] = d;
    if (index >= WAVE_BUFFER_SIZE)
    {
        index = 0;
        waveFile.write((char *)data.waveformData, WAVE_BUFFER_SIZE *2);
    }
    length+=2;
}

/*----------------------------------------------------------------------*/
/* This method write end of buffer (if any) and close the wave file.    */
/* Then it updates file headers to correct chunkSize value.		*/
/*----------------------------------------------------------------------*/
void WaveWriter::close()
{
    if (skip_save == true)
    {
        return;
    }

    // still something to save.
    if (index > 0)
    {
        waveFile.write((char *)data.waveformData, index *2);
    }

    // Update wave header.
    data.chunkSize = (int)length;
    waveFile.seekp(36);
    waveFile.write((char *)&data, sizeof(DataChunk) );
    waveFile.close();
}








