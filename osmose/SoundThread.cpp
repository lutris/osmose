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
 * File : SoundThread.cpp
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Wed Dec 15 07:43:05 2010
 *
 */

#include "SoundThread.h"

/**
 * Constructor.
 */
SoundThread::SoundThread(const char *devName, FIFOSoundBuffer *sb)
{
	/* Make a deep copy of the device name */
	strncpy(deviceName, devName, DEVICE_NAME_LENGTH);
	initAlsa();
	state = Paused;
	mutex = PTHREAD_MUTEX_INITIALIZER;
	sndFIFO = sb;
}

/**
 * Destructor.
 */
SoundThread::~SoundThread()
{
	
	// Set state to stopped and join ourself.
	state = Stopped;
	this->join(NULL);
	
	// THEN, close the audio device.
	snd_pcm_close (playback_handle);
}

/**
 * This is the main Sound thread loop.
 */
void* SoundThread::run(void *p)
{
	SoundThreadState local_state_copy;
	
	{
		MutexLocker lock(&mutex);
		local_state_copy = state;
	}

	
	while(local_state_copy != Stopped)
	{
		switch(local_state_copy)
		{
		
			case Playing:
				play();
			break;
				
			case Paused:
				struct timespec rqtp;
				rqtp.tv_sec = 0;
				rqtp.tv_nsec = 1000000; // 1 millisecond.
				nanosleep(&rqtp, NULL);	// NULL = dont care about remaining time if interrupted.			
			break;
				
			default:
				// Stopped means that thread is terminating.
			break;
		}
		
		{	// Locked section.
			MutexLocker lock(&mutex);
			local_state_copy = state;
		}
	}
	
	// We are Leaving the thread.
	return (void *)0xDEADBEEF;
}

void SoundThread::play()
{
	int err;
	/* wait till the interface is ready for data, or 16 milli second
	   has elapsed.
	*/

	if ((err = snd_pcm_wait(playback_handle, 16)) < 0)
	{
		fprintf(stderr, "poll failed (%s)\n", strerror (errno));
	}
	
	/* find out how much space is available for playback data */
	
	if ((frames_to_deliver = snd_pcm_avail_update (playback_handle)) < 0)
	{
		if (frames_to_deliver == -EPIPE)
		{
			fprintf (stderr, "an xrun occured\n");
		}
		
		else
		{
			fprintf (stderr, "unknown ALSA avail update return value (%d)\n",
			         (int)frames_to_deliver);
		}
	}
	
	frames_to_deliver = frames_to_deliver > 4096 ? 4096 : frames_to_deliver;
	
	/* deliver the data */
	
	if (playback_callback (frames_to_deliver) != frames_to_deliver)
	{
		fprintf (stderr, "playback callback failed\n");
	}
}


int SoundThread::playback_callback (snd_pcm_sframes_t nframes)
{
	int err;
	
	//printf ("playback callback called with %d frames\n", (int)nframes);
	void *channelsbuffer[1];
	channelsbuffer[0] = &samplebuffer;
	sndFIFO->read(samplebuffer, nframes);
		
	if ((err = snd_pcm_writen(playback_handle, (void **)channelsbuffer, nframes)) < 0)
	{
		fprintf (stderr, "write failed (%s)\n", snd_strerror (err));
	}
	
	return err;
}


/**
 *
 */
void SoundThread::stop()
{
	MutexLocker lock(&mutex);	
	state = Stopped;

	// Perform ALSA shutdown !
}

/**
 *
 */
void SoundThread::pause()
{
	MutexLocker lock(&mutex);	
	state = Paused;

	// Perform ALSA Pause
}

/**
 *
 */
void SoundThread::resume()
{
	MutexLocker lock(&mutex);	
	state = Playing;
	// Perform ALSA start/continue !
}




/**
 * This method prepares ALSA system for 22050hz signed 16bits Little Endian
 * playback.
 */
void SoundThread::initAlsa()
{
	int err;
	ostringstream oss;
	
	/* Get a handle on the PCM device. */
	
	if ((err = snd_pcm_open (&playback_handle, deviceName, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		oss << "cannot open audio device : " << deviceName << snd_strerror(err) << endl;
		throw oss.str();
	}
	
	/* Allocate snd_pcm_hw_params_t structure. */
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
	{
		oss << "cannot allocate hardware parameter structure : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Retrieve current parameters. */
	if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0)
	{
		oss << "cannot initialize hardware parameter structure : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	
	/* Set Sample are NON Interleaved (mono !) */
	if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_NONINTERLEAVED)) < 0)
	{
		oss << "cannot set access type : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Set Sample format: Signed 16bit little endian. */
	if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0)
	{
		oss << "cannot set sample format : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Set the Sample rate. */
	if ((err = snd_pcm_hw_params_set_rate (playback_handle, hw_params, 22050, 0)) < 0)
	{
		oss << "cannot set sample rate : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Set Channel number (MONO). */
	if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, 1)) < 0)
	{
		oss << "cannot set channel count : " << snd_strerror (err) << endl;
		throw oss.str();
	}

	
	if ((err = snd_pcm_hw_params_set_buffer_size(playback_handle, hw_params, 2048)) < 0)
	{
		oss << "cannot set channel buffer size : " << snd_strerror (err) << endl;
		throw oss.str();
	}

	

	/* Apply these parameters. */
	if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0)
	{
		oss << "cannot apply parameters : " << snd_strerror (err) << endl;
		throw oss.str();
	}

	snd_pcm_uframes_t bufferSize;
	snd_pcm_hw_params_get_buffer_size( hw_params, &bufferSize );
	//cout << "initAlsa: Buffer size = " << bufferSize << " frames." << endl;
	
	/* Free memoray allocated for snd_pcm_hw_params_t */
	snd_pcm_hw_params_free (hw_params);
	
	/* tell ALSA to wake us up whenever 4096 or more frames
	   of playback data can be delivered. Also, tell
	   ALSA that we'll start the device ourselves.
	*/
	
	/* Allocate snd_pcm_sw_params_t structure. */
	if ((err = snd_pcm_sw_params_malloc (&sw_params)) < 0)
	{
		oss << "cannot allocate software parameters structure : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Get the current software configuration*/
	if ((err = snd_pcm_sw_params_current (playback_handle, sw_params)) < 0)
	{
		oss << "cannot initialize software parameters structure : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Set the wake up point to 2048 (92.9 ms). The minimum data available before asking*/
	/* for new ones. */
	if ((err = snd_pcm_sw_params_set_avail_min (playback_handle, sw_params, 2048U)) < 0)
	{
		oss << "cannot set minimum available count : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Set when ALSA starts to play. */
	if ((err = snd_pcm_sw_params_set_start_threshold (playback_handle, sw_params, 1024U)) < 0)
	{
		oss << "cannot set start mode : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* Apply parameters. */
	if ((err = snd_pcm_sw_params (playback_handle, sw_params)) < 0)
	{
		oss << "cannot apply software parameters : " << snd_strerror (err) << endl;
		throw oss.str();
	}
	
	/* the interface will interrupt the kernel every 4096 frames, and ALSA
	   will wake up this program very soon after that.
	*/
	
	if ((err = snd_pcm_prepare (playback_handle)) < 0)
	{
		oss << "cannot prepare audio interface for use : " << snd_strerror (err) << endl;
		throw oss.str();
	}
}
