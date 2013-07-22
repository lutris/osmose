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
 * File: TGAWriter.cpp
 * Project: Osmose
 *
 * Description: This file handle creation, and write into an uncompressed TGA
 * 24bits imagefile. No more formats supported.
 *
 * Author: Vedder Bruno
 * Date: 12/12/2007
 * URL: http://bcz.asterope.fr
 */

#include "TGAWriter.h"

TGAWriter::TGAWriter(char *filename, int width, int height)
{
	/* Initialise TGA Header with the given informations.*/
	header.identsize = 0;
	header.colourmaptype = 0;	/* No palette.  */
	header.imagetype = 2;		/* RGB picture. */
	header.colourmapstart = 0;	/* No colormap. */
	header.colourmaplength =0;
	header.colourmapbits = 0;
	header.xstart = 0;
	header.ystart = 0;
	header.width = width;
	header.height = height;
	header.bits = 24;			/* 24Bits RGB.  */
	header.descriptor = 0;

	tgaFile = new ofstream(filename, ios::binary | ios::out);
	isOk_ = tgaFile->is_open();
	tgaFile->write((char *)&header, sizeof(TGAHeader));
	cacheIndex = 0;
}


TGAWriter::~TGAWriter()
{
	flushCache();
	tgaFile->close();
}

void TGAWriter::writePixel(unsigned char r, unsigned char g,unsigned char b)
{
	if (cacheIndex > INTERNAL_CACHE_SIZE -3)
	{
		flushCache();
	}
	cache[cacheIndex++] = b;
	cache[cacheIndex++] = g;
	cache[cacheIndex++] = r;
}

void TGAWriter::flushCache()
{
	if (cacheIndex != 0)
	{
		tgaFile->write((char *)cache, cacheIndex);
	}
	cacheIndex = 0;
}
