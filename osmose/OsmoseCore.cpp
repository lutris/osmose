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
 * File: OsmoseCore.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This file contains Osmose main loop, handling keyboard, SDL
 * event, and hardware emulation.
 *
 * Author: Vedder Bruno
 * Date: 23/01/2005, 14h13
 *
 * URL: http://bcz.asterope.fr
 */
 
#include "OsmoseCore.h"


SN76489           *p;

// This method is not from OsmoseCore
void sndCallback(void *ud, unsigned char *s, int len);

/*--------------------------------------------------------------------*/
/* This method is the OsmoseCore constructor.			      */
/*--------------------------------------------------------------------*/
OsmoseCore::OsmoseCore(const char *rom_f,  unsigned int *output, OsmoseConfigurationFile *conf, pthread_mutex_t *ocm)
{
	osmose_core_mutex = ocm;
	configuration = conf;
	buffer = output;
    nmi		   = false;
    sound_shot_toggle = false;
    snd_started = false;
    screenshotNbr  = 0;
    tileshotNbr	   = 0;
    soundshotNbr   = 0;
    rom_filename   = rom_f;
    gain = 0.00f;

	opt.reset();
    /* Note: After instantiation, opt.MachineType contains SMS or GAMEGEAR type. */
    mem  = new MemoryMapper(rom_filename, configuration);
    if (opt.mapperType == CodemasterMapper) mem->setMapperType(CodemasterMapper);
    if (opt.mapperType == KoreanMapper) mem->setMapperType(KoreanMapper);

    env  = new SmsEnvironment();
    cpu  = new Z80(*env);

    p    = new SN76489(3579545, 22050);

    if (opt.MachineType == SMS)
    {
        v    = new VDP(cpu, opt.ntsc);   // Instanciate ntsc or pal SMS VDP.
        iom  = new IOMapper(*v, *p);
    }
    else
    {
        // Instanciate ntsc (always) GAMEGEAR VDP. Force emulator option too.
        v = new VDP_GG(cpu, true);
        opt.ntsc = true;
        iom  = new IOMapper_GG(*v, *p);
    }

    env->setIOMapper(iom);
    env->setMemoryMapper(mem);
    env->setVDP(v);
    env->setCPU(cpu);
    wavW = NULL;
    game_name = mem->getROMName();

#ifdef BUILT_IN_DEBUGGER
    dbg  = new SmsDebugger();
    v->attachDebugEventListener(dbg);
    this->attachDebugEventListener(dbg);
    cpu->attachDebugEventListener(dbg);
    mem->attachDebugEventListener(dbg);
    iom->attachDebugEventListener(dbg);
    dasm = new Z80Dasm(*env);
    dbg->setMemoryMapper(mem);
    dbg->setEnvironment(env);
    dbg->setVDP(v);
    dbg->setIOMapper(iom);
    dbg->setDasm(dasm);
    dbg->setCPU(cpu);
    old_cycles = 0;
#endif


	emu_opt.sound = true;

    if (emu_opt.sound == true)
    {
		try
		{
			sndThread = new SoundThread("plughw:0,0", p->getFIFOSoundBuffer());
			sndThread->start(); 	// Start thread, not playing !		
			string msg = "Creating SoundThread";
			QLogWindow::getInstance()->appendLog(msg);
		}
		catch(string error)
		{
			QLogWindow::getInstance()->appendLog(error);
			QLogWindow::getInstance()->appendLog("Sound disabled. Sound recording wont work.");
			sndThread = NULL;
			emu_opt.sound = false;
		}
	}
}

/*--------------------------------------------------------------------*/
/* This method is the OsmoseCore destructor.			              */
/*--------------------------------------------------------------------*/
OsmoseCore::~OsmoseCore()
{
	if (wavW != NULL) delete wavW;
	if (sndThread != NULL) delete sndThread;
	save_bbr();	/* Save Battery backed memory if needed. */
	delete v;
	delete mem;
	delete env;
	delete iom;
	delete cpu;	
}

/*--------------------------------------------------------------------*/
/* This method performs a reset on all machine components.	          */
/*--------------------------------------------------------------------*/
void OsmoseCore::reset()
{
	MutexLocker lock(osmose_core_mutex);
	save_bbr();
	cpu->reset();
	v->reset();
	mem->reset();
	iom->reset();
}


/*--------------------------------------------------------------------*/
/* This method runs one frame.									      */
/* Note about frame variable:									      */
/* This variable is the total number of frame (displayed or not !)    */
/* emulated by Osmose. This value is use for speed synchronisation at */
/* 60 Fps. That's why the value is incremented even if the frame isn't*/
/* rendered.                                                          */
/*--------------------------------------------------------------------*/
void OsmoseCore::run_frame()
{
	MutexLocker lock(osmose_core_mutex);	

    bool drawline    = true;
    bool played      = false;
    float snd_update = 0;
    int scanline_number;
    unsigned int over_cycles = 0;
	
    scanline_number = (opt.ntsc == true) ? 262 : 313; // NTSC or PAL

    if (nmi == true)
    {
        cpu->nmi();
        nmi = false;
    }
			
    for (v->line=0; v->line < scanline_number; v->line++)
    {
        over_cycles = cpu->run(CPU_CYCLES_PER_LINE - over_cycles);
        if (emu_opt.sound == true)
        {
            snd_update+=(float)SND_TOGGLE;  // Needed to call update_sound_buffer 367.5/frame
            played = p->run(1);

            if ((sound_shot_toggle == true) && (played == true))
            {
                wavW->writeData(p->getLastSample());
            }

            if (snd_update > 1.0f)
            {
                played = p->run(1);
                if (played == true)
                {
                    snd_update = snd_update - (float)1.0f;
                }
                if (sound_shot_toggle == true && played==true)
                {
                    wavW->writeData(p->getLastSample());
                }
            }
        }
        v->update(buffer, drawline);
    } // For i = 0 to scanline_number

    //tw->update(buffer, drawline);

    if ((snd_started == false) && (emu_opt.sound == true))
    {
		// Start playing only if sound buffer is full.
        // This avoid playing silence on emulator startup.
        if (!p->getFIFOSoundBuffer()->spaceAvailable())
        {
            snd_started = true;
			sndThread->resume();	
        }
    }

    // To avoid infinite loop with cycleCounter overflow.
    cpu->setCycles(0);
}


/*--------------------------------------------------------------------*/
/* This method will save as bitmap, vdp graphics tiles.		      */
/* First, a 128x224 SDL_Surface is allocated.			      */
/* Then tiles are drawn there.					      */
/* A screenshot is taken					      */
/* The Surface is freed.					      */
/* Filename is tiles_rip_ + game_name.bmp.			      */
/*--------------------------------------------------------------------*/
bool OsmoseCore::captureTiles()
{
	MutexLocker lock(osmose_core_mutex);	
	
	ostringstream oss;
	oss << configuration->getTileCapturePath() << "/" << game_name << "-" << tileshotNbr << "_Tiles_Rip.tga";
	tileshotNbr++;

	/* Allocate 128x224 buffer */
	unsigned int *local_buffer = new unsigned int[128*224];
	unsigned int map_p = 0;
	
	/* Render tiles into the buffer. */
    // Draw tiles there.
    for (int o=0; o<28;o++)
	{
		int tile = 0;
        for (int i=0; i<16;i++)
        {
            int tile = map_p;
            displayTiles(local_buffer, v, tile, i<<3, o<<3);
            map_p++;
        }	
	}
	
	/* Save the buffer. */
	TGAWriter tgaFile((char *)oss.str().c_str(), 128, 224);
	if (tgaFile.isOk() == true)
	{
		for (int y=223; y>=0; y--)
		{
			int index = y * 128;
			for (int x= 0; x<128; x++)
			{
				unsigned char r, g, b;
				unsigned int d = local_buffer[index++];
				b = (d >> 16) & 0xFF;
				g = (d >> 8) & 0xFF;
				r = d & 0xFF;
				tgaFile.writePixel(r, g, b);					
			}
		}
	}
	else
	{
		return false;
	}
	
	/* Deallocate buffer. */
	delete local_buffer;
	
	return true;
}


/*--------------------------------------------------------------------*/
/* This method draws a tile n, at position x,y, assuming that the     */
/* Surface is 128 pixels wide.					      */
/*--------------------------------------------------------------------*/


void OsmoseCore::displayTiles(unsigned int *s, VDP *vd, int tile, int x, int y)
{
    unsigned int *ptr;
    unsigned char col_index, p0, p1, p2, p3;
    unsigned int ti, c;

    ti = tile<<5;
    ptr = (unsigned int *)s + ((y<<7)+x );
    for (int o=0; o<8;o++)
    {
        c = (o<<2) + ti;
        p0 = vd->VRAM[c++];
        p1 = vd->VRAM[c++];
        p2 = vd->VRAM[c++];
        p3 = vd->VRAM[c++];

        for (int i=0; i<8;i++)
        {
            col_index = (p0 >>7) | (p1 >> 7)<<1 | (p2 >> 7)<<2 | (p3 >> 7)<<3;
            *(unsigned int *)ptr = vd->colors[col_index];
            ptr++;
            p0<<=1;
            p1<<=1;
            p2<<=1;
            p3<<=1;
        }
        ptr += 120; // Complement to next line, based on 256 pixel width.
    }
}


/*--------------------------------------------------------------------*/
/* This method is called by SDL sound system, to fill the sound buffer*/
/* s is the place to put sound data, len is length of buffer in bytes.*/
/*--------------------------------------------------------------------*/
void sndCallback(void *, unsigned char *s, int len)
{
    p->getWave(s, len);
}


/*--------------------------------------------------------------------*/
/* This method takes a screenshot of the game. The filename is        */
/* game_name +x .tga , where x is the number of taken screenshot,     */
/* which is incremented every time captureScreen() is called.         */
/*--------------------------------------------------------------------*/
bool OsmoseCore::captureScreen()
{
	MutexLocker lock(osmose_core_mutex);
	
	ostringstream oss;
	oss << configuration->getScreenshotPath() << "/" << game_name << "-" << screenshotNbr << ".tga";
	screenshotNbr++;

	TGAWriter tgaFile((char *)oss.str().c_str(), 256, 192);
	if (tgaFile.isOk() == true)
	{
		for (int y=191; y>=0; y--)
		{
			int index = y * 256;
			for (int x= 0; x<256; x++)
			{
				unsigned char r, g, b;
				unsigned int d = buffer[index++];
				b = (d >> 16) & 0xFF;
				g = (d >> 8) & 0xFF;
				r = d & 0xFF;
				tgaFile.writePixel(r, g, b);					
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

/*--------------------------------------------------------------------*/
/* This method toggles the sound recording on and OFF. The filename   */
/* is game_name +x .wav , where x is the number of taken sound shot,  */
/* which is incremented every time recordSounds(OFF) is called.       */
/* Return : true if operation was successfull, false otherwise. 	  */
/*--------------------------------------------------------------------*/
bool OsmoseCore::startRecordingSounds()
{
	MutexLocker lock(osmose_core_mutex);
	
	bool retValue = false;
	ostringstream oss;

	oss << configuration->getSoundCapturePath() << "/" << game_name << "-" << soundshotNbr << ".wav";

    wavW = new WaveWriter(oss.str().c_str());
	if (wavW->isOk())
	{
		soundshotNbr++;
		sound_shot_toggle = true;
		retValue = true;
	}
	return retValue;
}

/*--------------------------------------------------------------------*/
/* This method toggles the sound recording on and OFF. The filename   */
/* is game_name +x .wav , where x is the number of taken sound shot,  */
/* which is incremented every time recordSounds(OFF) is called.       */
/* Return : true if operation was successfull, false otherwise. 	  */
/*--------------------------------------------------------------------*/
void OsmoseCore::stopRecordingSounds()
{
	MutexLocker lock(osmose_core_mutex);
	
    wavW->close();
    delete wavW; // To avoid memory leak.
	wavW = NULL;
	sound_shot_toggle = false;
}

/*--------------------------------------------------------------------*/
/* This method generates save state file. Here is the format:         */
/* File Offset - Data type.                                           */
/* 0000-0003     unsigned char[4] marker "OESS"                       */
/* 0004-0007     unsigned char[4] 0 + version that create savestate.  */
/* 0008-0019     unsigned char[18] z80_8bits_registers.               */
/* 001A-0021     unsigned short[4] z80_16bits_registers.              */
/*--------------------------------------------------------------------*/
bool OsmoseCore::saveSaveState(int slot)
{
	MutexLocker lock(osmose_core_mutex);
	
    ostringstream save_state_name;

    save_state_name << configuration->getSaveStatePath() << "/" << mem->getROMName() << "_slot_" << slot <<".sta";

    ofstream output_file((char *)save_state_name.str().c_str(), ios::out | ios::binary );
    if (output_file.is_open() == false )
    {
		string msg = "Cannot create save state file:" + save_state_name.str();
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }

    /* Write cpu data. */
    if (!cpu->saveState( output_file ) )
    {
		string msg = "CPU save failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }

    /* Write memory mapper data. */
    if (!mem->saveState( output_file ) )
    {
		string msg = "Mem Mapper save failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }

    /* Write VDP data. */
    if (!v->saveState( output_file ) )
    {
		string msg = "VDP save failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }

    /* Write SN76489 data. */
    if (!p->saveState( output_file ) )
    {
		string msg = "PSG save failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }
    output_file.close();
	string msg = "State saved in file :" + save_state_name.str();
	QLogWindow::getInstance()->appendLog(msg);
    return true;
}


/*--------------------------------------------------------------------*/
/* This method loads an emulation state previously saved.             */
/*--------------------------------------------------------------------*/
bool OsmoseCore::loadSaveState(int slot)
{
	MutexLocker lock(osmose_core_mutex);
	
    ostringstream load_state_name;
    load_state_name << configuration->getSaveStatePath() << "/" << mem->getROMName() << "_slot_" << slot <<".sta";

    ifstream input_file((char *)load_state_name.str().c_str(), ios::in | ios::binary);
    if (input_file.is_open() == false )
    {
		string msg = "Fail to load state from file : " + load_state_name.str();
		QLogWindow::getInstance()->appendLog(msg);	
        return false;
    }

    /* Load cpu data. */
    if (!cpu->loadState( input_file ) )
    {
		string msg = "CPU load failed.";
		QLogWindow::getInstance()->appendLog(msg);		
        return false;
    }

    /* Load memory mapper data. */
    if (!mem->loadState( input_file ) )
    {
		string msg = "Mem Mapper load failed.";
		QLogWindow::getInstance()->appendLog(msg);	
		return false;
    }

    /* Load VDP data. */
    if (!v->loadState( input_file ) )
    {
		string msg = "VDP load failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }

    /* Save SN76489 data. */
    if (!p->loadState( input_file ) )
    {
		string msg = "PSG load failed.";
		QLogWindow::getInstance()->appendLog(msg);
        return false;
    }
    input_file.close();
	string msg = "State loaded from file : " + load_state_name.str();
	QLogWindow::getInstance()->appendLog(msg);
    return true;
}


/*--------------------------------------------------------------------*/
/* This method saves Battery Backed Memory if needed.                 */
/*--------------------------------------------------------------------*/
void OsmoseCore::save_bbr()
{
	// No need to lock mutex, method is private and only called via reset or locked method.
    ostringstream bbr_name;
    bbr_name << configuration->getBBRPath() << "/" << game_name.c_str() << ".bbr";
    mem->save_battery_backed_memory(bbr_name.str());
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 Up key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1UpChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT0_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT0;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 Down key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1DownChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT1_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT1;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 Left key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1LeftChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT2_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT2;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 right key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1RightChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT3_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT3;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 A key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1AButtonChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT4_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT4;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P1 B key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P1BButtonChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT5_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT5;
	}
}



/*--------------------------------------------------------------------*/
/* This method is called when P2 Up key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2UpChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT6_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT6;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P2 Down key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2DownChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD1 &= BIT7_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD1 |= BIT7;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P2 Left key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2LeftChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD2 &= BIT0_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD2 |= BIT0;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P2 right key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2RightChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD2 &= BIT1_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD2 |= BIT1;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P2 A key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2AButtonChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD2 &= BIT2_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD2 |= BIT2;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when P2 B key changed is triggered.         */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::P2BButtonChanged(bool pressed)
{
	if (pressed)
	{
		iom->portPAD2 &= BIT3_MASK;;
	}
	else
	{
		// Key released.
		iom->portPAD2 |= BIT3;
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when Pause button is triggered.	          */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::PauseButtonChanged(bool pressed)
{
	if (pressed)
	{
		// Game Gear has no pause button !
		if (opt.MachineType == SMS)	nmi = true;
	}
	else
	{
		// No NMIes are triggered on pause released.
	}
}


/*--------------------------------------------------------------------*/
/* This method is called when Game Gear Start is triggered.           */
/* If parameter pressed is false, it means that key is released,      */
/* pressed otherwise. This callback is called whatever the input      */
/* device is used.                                                    */
/*--------------------------------------------------------------------*/
void OsmoseCore::StartButtonChanged(bool pressed)
{
	// SMS has no start button !
	if (opt.MachineType != GAMEGEAR) 
	{
		return;
	}
	
	if (pressed)
	{
		iom->port0x0 &= BIT7_MASK;
	}
	else
	{
		iom->port0x0 |= BIT7;
	}
}

/*--------------------------------------------------------------------*/
/* This method is used to force memory mapper selection.              */
/*--------------------------------------------------------------------*/
void OsmoseCore::forceMemoryMapper(Mapper mapper)
{
	MutexLocker lock(osmose_core_mutex);
	mem->setMapperType(mapper);
}


/*--------------------------------------------------------------------*/
/* This method is used to force NTSC or PAL timings.                  */
/* true = NTSC false=PAL                                              */
/*--------------------------------------------------------------------*/
void OsmoseCore::forceNTSCTiming(bool ntsc)
{
	MutexLocker lock(osmose_core_mutex);
	v->setNTSC(ntsc);
}
