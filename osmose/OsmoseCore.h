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
 * File: OsmoseCore.h
 *
 * Project: Osmose emulator.
 *
 * Description: This file contains Osmose main loop, handling keyboard,
 * event, and hardware emulation.
 *
 * Author: Vedder Bruno
 * Date: 23/01/2005, 14h13
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef OSMOSE_CORE_H
#define OSMOSE_CORE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <pthread.h>

#include "Z80.h"
#include "SmsEnvironment.h"
#include "OsmoseConfigurationFile.h"
#include "VDP.h"
#include "VDP_GG.h"
#include "SN76489.h"
#include "Options.h"
#include "Bits.h"
#include "WaveWriter.h"
#include "Version.h"
#include "Definitions.h"
#include "DebugEventThrower.h"
#include "SaveState.h"
#include "AnsiColorTerminal.h"
#include "EmulationThread.h"
#include "TGAWriter.h"
#include "QLogWindow.h"
#include "Pthreadcpp.h"
#include "SoundThread.h"

using namespace std;



/* Use save state slot from 1 to 5. */
enum
{
    minSaveStateSlot = 1,
    maxSaveStateSlot = 5
};

class OsmoseCore : public DebugEventThrower
{

    public:

        OsmoseCore(const char *rom_f, unsigned int *output, OsmoseConfigurationFile *c, pthread_mutex_t *ocm);	// Constructor.
        ~OsmoseCore();
		void run_frame();				// Run one Frame.
        
        void Reshape(int x, int y);
        void reset();					// Reset all components.

		void P1UpChanged(bool pressed);
		void P1DownChanged(bool pressed);		
		void P1LeftChanged(bool pressed);
		void P1RightChanged(bool pressed);
		void P1AButtonChanged(bool pressed);
		void P1BButtonChanged(bool pressed);
		void P2UpChanged(bool pressed);
		void P2DownChanged(bool pressed);		
		void P2LeftChanged(bool pressed);
		void P2RightChanged(bool pressed);
		void P2AButtonChanged(bool pressed);
		void P2BButtonChanged(bool pressed);
		void PauseButtonChanged(bool pressed);
		void StartButtonChanged(bool pressed);
		bool captureScreen();
		bool captureTiles();
		bool startRecordingSounds();
		void stopRecordingSounds();
		bool saveSaveState(int slot);
        bool loadSaveState(int slot);

		void forceMemoryMapper(Mapper m);
		void forceNTSCTiming(bool);
		
		private:

        unsigned int        *buffer;     // SMS screen, without modification 256x192.
        string               game_name;  // Used as prefix for screenshot, sound shot and save states.
        VDP                 *v;	     	 // Video Display Processor object.
        MemoryMapper        *mem;        // Memory mapper Object.
        SmsEnvironment      *env;        // Z80 Cpu environment.
        IOMapper            *iom;        // Input/Output mapper Object.
        Z80                 *cpu;	     // Our Z80 core.
        WaveWriter          *wavW;       // Sound ripper.
        float               gain;        // gain level.

#ifdef BUILT_IN_DEBUGGER
        unsigned int   old_cycles;	    // Used for cycle count.
        Z80Dasm        *dasm;	     	// Z80 disasembler object.
        SmsDebugger    *dbg;	     	// Sms Debugger.
        bool           exec_f;          // Continue cpu exec Flag.
#endif

        bool nmi;					// nmi flag, used with keyboard pause.
        bool sound_shot_toggle;		// Flag, for start/stop recording sound.
        int  screenshotNbr;			// Screenshot number appended to save.
        int  tileshotNbr;			// Tile rip  number appended to save.
        int  soundshotNbr;			// Sound rip  number appended to save.
        const char *rom_filename;	// Pointer to argv[1].

        bool snd_started;

        void save_bbr();				// Save Battery Backed Ram.
        
        void displayTiles(unsigned int *s, VDP *vd, int tile, int x, int y);
		SoundThread *sndThread;
		OsmoseConfigurationFile *configuration;
		pthread_mutex_t *osmose_core_mutex;
};

#endif
