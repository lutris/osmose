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
 * File : EmulationThread.h
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Fri May 21 14:05:52 2010
 *
 */

#ifndef EMULATIONTHREAD_H
#define EMULATIONTHREAD_H

#include <iostream>
#include <sys/time.h>
#include <QThread>
#include <QReadWriteLock>
#include "QGLImage.h"
#include "OsmoseConfigurationFile.h"

using namespace std;

class EmulationThread : public QThread
{
	Q_OBJECT;
	
	enum EmulationState
	{
		EMULATION_STOPPED = 0,
		EMULATION_RUNNING,
		EMULATION_ABORTED
	};
	
public:
	EmulationThread(QGLImage *qglimage);
	virtual ~EmulationThread();
	void abortEmulation();
	
public slots:
	void pauseEmulation();
	void resumeEmulation();
	void startEmulation();
	virtual void resetEmulation();
	virtual void keyPressed(padKey key);
	virtual void keyReleased(padKey key);
	
	
	
signals:
	void newResolution(int w, int h);

protected:

	unsigned int *videoBuffer;
	void run();
	virtual void emulateOneFrame() = 0;
	void setRefreshFrequency(float usec);
	void setResolution(int w, int h);
		
private:
	bool done;
	QReadWriteLock emulationStateQMutex;
	QGLImage *screen;
	unsigned int refreshingPeriod;
	EmulationState emulationState;	
};

#endif	// EMULATIONTHREAD_H
