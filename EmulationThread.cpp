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
 * File : EmulationThread.cpp
 *
 * Description : This class provide basic EmulationThread feature. It can start
 * pause, resume the rendering code that is provided in emulateOneFrame() pure
 * virtual method. The setRefreshingPeriod() set the number of frame per second
 * that is wanted. emulatOneframe() is called accordingly. The setResolution()
 * method emits a newResolution() signal to the QGLimage object to inform it 
 * of a resolution change (e.g. emulated video mode switch). The texture buffer
 * videoBuffer is allocated accordingly.
 * This class MUST be inherited, and the derived class MUST provide the 
 * emulateOneFrame() function, which perform emulation task and fill the video
 * buffer.
 *
 * Author : B.Vedder
 *
 * Date : Fri May 21 14:05:52 2010
 *
 */

#include "EmulationThread.h"

/**
 * Constructor.
 */
EmulationThread::EmulationThread(QGLImage *qglimage) : screen(qglimage)
{
	// Allocate buffer of the texture size.
	videoBuffer = NULL;
	QObject::connect(this, SIGNAL(newResolution(int, int)), qglimage, SLOT(resolutionChanged(int, int)));
	setResolution(qglimage->getTextureWidth(), qglimage->getTextureHeight());
	emulationState = EMULATION_STOPPED;
	
	// Set default refresh slow arbitrary frequency.
	setRefreshFrequency(1.0f);
	done = false;
}

/**
 * Destructor.
 */
EmulationThread::~EmulationThread()
{
	delete []videoBuffer;
}

/**
 * This method overrides QThread run(). It's the thread main method.
 * 
 * Return : None.
 */
void EmulationThread::run()
{
	struct timeval t0, t1;
	struct timespec rqtp, rmtp;
	unsigned int deltaT_micros, remainingT;
	
	while(!done)
	{
		emulationStateQMutex.lockForRead();
		switch(emulationState)
		{
			case EMULATION_STOPPED:
				// Free QMutex.
				emulationStateQMutex.unlock();
				
				// Sleep 20ms.
				rqtp.tv_sec = 0;
				rqtp.tv_nsec = 20 * 1000 * 1000; // 20 millisecond.	
				nanosleep(&rqtp, &rmtp);
			break;

			case EMULATION_RUNNING:
				// Free QMutex.
				emulationStateQMutex.unlock();
				
				// Execute one emulation frame, blit texture into openGL
				// and calculate the duration of these operations.
				gettimeofday(&t0, NULL);		
				emulateOneFrame();
				screen->blit(videoBuffer);
				gettimeofday(&t1, NULL);
				
				// Compute duration.
				deltaT_micros = ((t1.tv_sec * 1000000 + t1.tv_usec) - (t0.tv_sec * 1000000 + t0.tv_usec));
				
				// Compute remaining time to achieve the good regreshing period.
				remainingT = (deltaT_micros < refreshingPeriod) ? refreshingPeriod - deltaT_micros : 1;

				// Sleep the remaining time.
				rqtp.tv_sec = 0;
				rqtp.tv_nsec = remainingT * 1000; // microsecond to nanoseconds				
				nanosleep(&rqtp, &rmtp);
				//cout << "Loop takes :" << deltaT_micros << " microseconds, sleeping "<< remainingT << " microseconds "<< endl;		
			break;
			
			case EMULATION_ABORTED:
				done = true;
				emulationStateQMutex.unlock();	
			break;
			
			default:
				// Free QMutex.
				emulationStateQMutex.unlock();
				
			break;
		}
	}
}


/**
 * This method will abort Emulation. This will cause the emulation thread
 * to die.
 * 
 * Return : None.
 * 
 */
void EmulationThread::abortEmulation()
{
	QWriteLocker lock(&emulationStateQMutex);
	emulationState = EMULATION_ABORTED;
}


/**
 * This method will start Emulation. If emulation is already started, it
 * does nothing.
 * 
 * Return : None.
 * 
 */
void EmulationThread::startEmulation()
{
	QWriteLocker lock(&emulationStateQMutex);
	emulationState = EMULATION_RUNNING;
}


/**
 * This method will suspends Emulation. To continue, one should call
 * resume() method.
 * 
 * Return : None.
 *
 */
void EmulationThread::pauseEmulation()
{
	QWriteLocker lock(&emulationStateQMutex);
	emulationState = EMULATION_STOPPED;	
}

/**
 * This method will resume Emulation that has previously been stopped
 * using pauseEmulation();
 * 
 * Return : None.
 * 
 */
void EmulationThread::resumeEmulation()
{
	QWriteLocker lock(&emulationStateQMutex);
	startEmulation();
}

/**
 * This method will reset/restart Emulation. It's equivalent to a 
 * hardware reset.
 * 
 * Return : None.
 * 
 */
void EmulationThread::resetEmulation()
{
}

/**
 * This method set the refreshing period of the emulation thread.
 * Important note : The QThread::run method will call repeatly the
 * emulateOneFrame() methods which should perform emulation stuff for
 * exactly one frame. The execution time of emulateOneFrame() is 
 * calculated, and the remaining time to reach the refreshing period
 * is wasted in nanosleep.
 * 
 * Param 1 : The refresh frequency in Hertz of the emulation. This value 
 * should be the display original emulated refresh display.
 * 
 * Return : None.
 */
void EmulationThread::setRefreshFrequency(float f)
{
	float t = (1.0 / f);
	refreshingPeriod = (t * 1000000.0f); // to microseconds
	//cout << "refreshingPeriod = " << refreshingPeriod << " microsec." << endl;
}

/**
 * This method will change the textureSize that is mapped on the GL QUAD. It
 * usually happens on emulated video mode change. The texture buffer is 
 * deleted and reallocated, and a signal emitted to inform QGLimage of this
 * event.
 *
 * Param 1 : new texture width.
 * 
 * Param 2 : new texture height.
 *
 * Return : None.
 * 
 */
void EmulationThread::setResolution(int w, int h)
{
	delete []videoBuffer;
	int s = w * h;
	videoBuffer = new unsigned int[s];
	memset(videoBuffer, 0, s * sizeof(unsigned int));	
	emit newResolution(w, h);
}

/**
 * This method is used to receive key press trigger. It's not declared
 * as a slot in order to avoid slot connection/deconnection on ROM change.
 * To implement a different behaviour from the default one, simply override
 * this method.
 * 
 * Param 1 : QT key() value of the QKeyEvent that signal keyPressed.
 * 
 * Return : None. 
 */
void EmulationThread::keyPressed(padKey)
{

}


/**
 * This method is used to receive key press trigger. It's not declared
 * as a slot in order to avoid slot connection/deconnection on ROM change.
 * To implement a different behaviour from the default one, simply override
 * this method.
 * 
 * Param 1 : QT key() value of the QKeyEvent that signal keyPressed.
 * 
 * Return : None. 
 */
void EmulationThread::keyReleased(padKey)
{
}
