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
 * File : OsmoseEmulationThread.h
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Thu May 27 14:20:27 2010
 *
 */
#ifndef OSMOSE_EMULATION_THREAD_H
#define OSMOSE_EMULATION_THREAD_H

#include <pthread.h>
#include <Qt>
#include "EmulationThread.h"
#include "Z80.h"
#include "OsmoseCore.h"
#include "OsmoseConfigurationFile.h"


class OsmoseEmulationThread : public EmulationThread
{
public:
	OsmoseEmulationThread(QGLImage *qglimage, char *romName, OsmoseConfigurationFile *conf, pthread_mutex_t *ocm);
	~OsmoseEmulationThread();
	void emulateOneFrame();
	void resetEmulation();
	void keyPressed(padKey key);
	void keyReleased(padKey key);
	OsmoseCore *getCore() {return core;}
	
protected:

private:
	int frameCounter;
	int mode;
	OsmoseCore *core;
	OsmoseConfigurationFile *configuration;
	pthread_mutex_t *osmose_core_mutex;
};

#endif	// OSMOSE_EMULATION_THREAD_H
