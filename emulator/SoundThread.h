/**
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
 * File : SoundThread.h
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Wed Dec 15 07:43:05 2010
 *
 */

#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H

#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <alsa/asoundlib.h>

#include "FIFOSoundBuffer.h"
#include "Pthreadcpp.h"

using namespace std;

#define DEVICE_NAME_LENGTH 64


class SoundThread : public Thread
{

enum SoundThreadState
{
	Playing,
	Paused,
	Stopped
};

public:
	SoundThread(const char *devName, FIFOSoundBuffer *);
	void stop();
	void pause();
	void resume();
	
	~SoundThread();

protected:
	
	void* run(void *p);
	
private:

	char deviceName[DEVICE_NAME_LENGTH];
	snd_pcm_t *playback_handle;
	short samplebuffer[4096];
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;
	snd_pcm_sframes_t frames_to_deliver;

	void initAlsa();
	void play();
	int playback_callback (snd_pcm_sframes_t nframes);
	SoundThreadState state;
	pthread_mutex_t mutex;
	FIFOSoundBuffer *sndFIFO;
};

#endif	// SOUNDTHREAD_H
