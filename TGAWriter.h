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
 *
 *
 * File: TGAWriter.h
 * Project: Osmose
 *
 * Description: This file handle creation, and write into an uncompressed TGA
 * 24bits imagefile. No more formats supported.
 *
 * Author: Vedder Bruno
 * Date: 12/12/2007
 * URL: http://bcz.asterope.fr
 */

#ifndef TGA_WRITER_H
#define TGA_WRITER_H

#include <fstream>
#include <iostream>

using namespace std;

#define INTERNAL_CACHE_SIZE 4096

 struct TGAHeader 
{
    unsigned char  identsize;    	// size of ID field that follows 18 byte header (0 usually)
    unsigned char  colourmaptype;	// type of colour map 0=none, 1=has palette
    unsigned char  imagetype;    	// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
    short colourmapstart;     		// first colour map entry in palette
    short colourmaplength;    		// number of colours in palette
    char  colourmapbits;      		// number of bits per palette entry 15,16,24,32
    short xstart;             		// image x origin
    short ystart;             		// image y origin
    short width;              		// image width in pixels
    short height;             		// image height in pixels
    unsigned char  bits;          	// image bits per pixel 8,16,24,32
    unsigned char  descriptor;    	// image descriptor bits (vh flip bits)
} __attribute__((packed));			// Required to avoid gcc to align data.

class TGAWriter
{
	public:

		TGAWriter(char *fn, int width, int height);
		~TGAWriter();
		bool isOk() {return isOk_;}
		void writePixel(unsigned char r, unsigned char g,unsigned char b);


	private:

		void flushCache();

		unsigned int cacheIndex;
		bool isOk_;
		struct TGAHeader header;
		ofstream *tgaFile;
		unsigned char cache[INTERNAL_CACHE_SIZE];
};

#endif

