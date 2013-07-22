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
 * File : OsmoseEmulationThread.cpp
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Thu May 27 14:20:27 2010
 *
 */

#include "OsmoseEmulationThread.h"


/**
 * Constructor.
 */
OsmoseEmulationThread::OsmoseEmulationThread(QGLImage *qglimage, char * romName, OsmoseConfigurationFile *conf, pthread_mutex_t *ocm) : EmulationThread(qglimage)
{
	configuration = conf;
	setRefreshFrequency(60.0f);
	frameCounter = 0;
	mode = 1;
	osmose_core_mutex = ocm;
	core = new OsmoseCore(romName, videoBuffer, configuration, osmose_core_mutex);
}


/**
 * Destructor.
 */
OsmoseEmulationThread::~OsmoseEmulationThread()
{	
	delete core;
}


/**
 * This method perform one frame emulation stuff. The videoBuffer must
 * be updated inside this method.
 */
void OsmoseEmulationThread::emulateOneFrame()
{
	core->run_frame();
}


/**
 * This method perform one frame emulation stuff. The videoBuffer must
 * be updated inside this method.
 */
void OsmoseEmulationThread::resetEmulation()
{
	core->reset();
}


/**
 * We get a Key Pressed event from the QMainWindow. Handle it. The
 * conversion from Emulator key mapping and user configuration occurs
 * here.
 * 
 * Param 1 : SMS/GG key.
 * 
 * Return : None. 
 */
void OsmoseEmulationThread::keyPressed(padKey key)
{
	switch(key)
	{
		case P1UP: 		core->P1UpChanged(true); 	break;
		case P1DOWN: 	core->P1DownChanged(true);	break;
		case P1LEFT:	core->P1LeftChanged(true);	break;
		case P1RIGHT:	core->P1RightChanged(true);	break;
		case P1BUTTON_A:core->P1AButtonChanged(true);break;
		case P1BUTTON_B:core->P1BButtonChanged(true);break;
		
		case P2UP: 		core->P2UpChanged(true); 	break;
		case P2DOWN: 	core->P2DownChanged(true);	break;
		case P2LEFT:	core->P2LeftChanged(true);	break;
		case P2RIGHT:	core->P2RightChanged(true);	break;
		case P2BUTTON_A:core->P2AButtonChanged(true);break;
		case P2BUTTON_B:core->P2BButtonChanged(true);break;		
		case PAUSE_NMI:	core->PauseButtonChanged(true);break;	
		case START_GG:	core->StartButtonChanged(true);break;
		case SCREENSHOT: core->captureScreen();

		case UNKNOWN : break;
		default: break;
	}
}


/**
 * We get a Key Released event from the QMainWindow. Handle it. The
 * conversion from Emulator key mapping and user configuration occurs
 * here.
 * 
 * Param 1 : QT key() value of the QKeyEvent that signal keyPressed.
 * 
 * Return : None. 
 */
void OsmoseEmulationThread::keyReleased(padKey key)
{
	switch(key)
	{
		case P1UP:		core->P1UpChanged(false);	break;
		case P1DOWN:	core->P1DownChanged(false);	break;
		case P1LEFT:	core->P1LeftChanged(false);	break;
		case P1RIGHT:	core->P1RightChanged(false);break;
		case P1BUTTON_A:core->P1AButtonChanged(false);break;
		case P1BUTTON_B:core->P1BButtonChanged(false);break;
		
		case P2UP: 		core->P2UpChanged(false); 	break;
		case P2DOWN: 	core->P2DownChanged(false);	break;
		case P2LEFT:	core->P2LeftChanged(false);	break;
		case P2RIGHT:	core->P2RightChanged(false);	break;
		case P2BUTTON_A:core->P2AButtonChanged(false);break;
		case P2BUTTON_B:core->P2BButtonChanged(false);break;				
		case PAUSE_NMI:	core->PauseButtonChanged(false);break;
		case START_GG:	core->StartButtonChanged(false);break;
		case UNKNOWN : break;
		default: break;
	}
}
