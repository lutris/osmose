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
 * File: SN76489.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will implements SN76489 functionnality.
 *
 * Author: Vedder Bruno
 * Date: 18/11/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
#include "SN76489.h"
#include "Bits.h"
//#include <stdio.h>

/* Values ripped from MEKA. They've been controlled against a real SMS.*/
const u16 SN76489::volume_table[16] = {892*5, 892*5, 892*5, 760*5, 623*5, 497*5, 404*5, 323*5, 257*5, 198*5, 159*5, 123*5,  96*5,  75*5,  60*5, 0};

#define MAX_OUTPUT 0x7FFF
/*--------------------------------------------------------------*/
/* Constructor.						 	*/
/*--------------------------------------------------------------*/
SN76489::SN76489(u32 chip_frequency, u32 samplingRate)
{
    if (chip_frequency > sn76489_max_clock) chip_frequency = sn76489_max_clock;
    if (chip_frequency < sn76489_min_clock) chip_frequency = sn76489_min_clock;
    chip_frequency_ = chip_frequency;
    clock_ = chip_frequency_ >> 4;
    update_step_ = (clock_ << 10) / samplingRate;
    Fifo_ = new FIFOSoundBuffer( 4096 );
    reset();
}

/*-------------------------------------------------------------*/
/* This method handles write operation on the PSG port.        */
/*-------------------------------------------------------------*/
void SN76489::writePort(u8 value)
{
    u8 channel;

    if (value & BIT7)	// Latch
    {
        lastRegister_ = (value >> 4) & 0x7;
        channel = lastRegister_ >> 1;
        if (value & BIT4)
        {
            volume_[channel] = value & 0xF;
#ifdef PSG_DEBUG
            printf("vol%d=%x.\n",(int)channel, (int)value & 0xF);
#endif
        }
        else
        {
            /* Like said in Maxim's doc, immediately update tone registers.*/
            freqDiv_[channel] = (freqDiv_[channel] & 0x3F0) | (value & 0xF);

            /*
               Channel 3 uses the same Freq Div than Channel 2. So when Ch2
               is updated, we must update Ch3 too.
             */
            if (channel==2 && follow_tone2_frequency_)
            {
                freqDiv_[3] = freqDiv_[2];
            }

#ifdef PSG_DEBUG
            if (channel !=3) printf("fd%d=%x.\n",(int)channel, freqDiv_[channel]);
#endif
        }
    }
    else		// Data byte write
    {
        channel = lastRegister_ >> 1;
        if (lastRegister_ & BIT0) // If true, it's volume register.
        {
            volume_[channel] = value & 0xF;
#ifdef PSG_DEBUG
            printf("vol%d=%x.\n",(int)channel, (int)value & 0xF);
#endif
        }
        else
        {
            if (channel !=3)
            {
                freqDiv_[channel] = (freqDiv_[channel] & 0xF) | ((value & 0x3F) << 4);
#ifdef PSG_DEBUG
                printf("fd%d=%x.\n",(int)channel, freqDiv_[channel]);
#endif
            }
        }
    }

    if (lastRegister_ == 0x6)
    {
#ifdef PSG_DEBUG
        printf("fd3=%x ",(int)channel, value & 0x3);
        if ((value & 0x3)== 3) printf("as ch2.\n");
        else printf(".\n");
#endif
        LFSR_ = NOISE_INITIAL_STATE;
        // Channel 3: writing 4bits 'tone' register.
        /* Only two bits are used with this Channel. */
        switch (value & 0x3)
        {
            case 0x0:
                freqDiv_[channel] = 0x10;
                follow_tone2_frequency_ = false;
                break;
            case 0x1:
                freqDiv_[channel] = 0x20;
                follow_tone2_frequency_ = false;
                break;
            case 0x2:
                freqDiv_[channel] = 0x40;
                follow_tone2_frequency_ = false;
                break;
            case 0x3:
                freqDiv_[channel] = freqDiv_[2];
                follow_tone2_frequency_ = true;
                break;
        }

        /* Select WhiteNoise/Periodic Noise from Noise BIT2. */
        whiteNoise_ = (value & BIT2);
    }
}


/*-------------------------------------------------------------*/
/* This method resets the PSG to it's initial values            */
/*-------------------------------------------------------------*/
void SN76489::reset()
{
    lastRegister_ = 0;
    whiteNoise_   = true;		// Default Periodic Noise.
    follow_tone2_frequency_ = false;
    LFSR_ = WHITE_NOISE_FEEDBACK;

    for (u32 i=0; i<4; i++)
    {
        volume_[i] = 0xF;
        half_period_[i] = 0;
        channel_output_[i] = 1;
        period_counter_[i] = 0;
    }
    Fifo_->reset();
}

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/
void SN76489::getWave(u8 *s, s32 len)
{
    s16 *dst = (s16 *)s;
    len >>= 1;
    Fifo_->read(dst, len);
}

/*-------------------------------------------------------------*/
/* This method returns parity of the given value.              */
/* Given by Maxim's SN76489 Documentation.		       */
/*-------------------------------------------------------------*/
u8 SN76489::parity(u16 val)
{
    val^=val>>8;
    val^=val>>4;
    val^=val>>2;
    val^=val>>1;
    return val & 1;
}

/*---------------------------------------------------------------*/
/* This method returns false is a sample is not accepted by Fifo.*/
/*---------------------------------------------------------------*/
bool SN76489::run(u32 cycles)
{
    if (!Fifo_->spaceAvailable()) return false;
    while ( cycles )
    {
        s16 snd = 0;

        /* Compute half periods for all channels. */
        for (u32 channel = 0; channel < 4; channel++)
        {
            half_period_[channel] = freqDiv_[channel] << 10;
            if (period_counter_[channel] >= half_period_[channel])
            {
                period_counter_[channel] = 0;
            }
        }

        /* Generate output for 3 channels (0 or 1) */
        for (u32 channel = 0; channel < 3; channel++)
        {
            period_counter_[channel] += update_step_;
            if (period_counter_[channel] >= half_period_[channel])
            {
                period_counter_[channel] -= half_period_[channel];
                channel_output_[channel] ^= 1;
            }
        }

        /* Generate output for Noise generator. */
        period_counter_[3] += update_step_;
        if (period_counter_[3] >= half_period_[3])
        {
            period_counter_[3] -= half_period_[3];
            LFSR_=(LFSR_>>1) | ((whiteNoise_ ? parity(LFSR_ & 0x9):LFSR_ & 1)<<15);
            channel_output_[3] =(LFSR_ & 1);
        }

        /* Now, generate samples for channels A, B and C. */
        for (u32 channel = 0; channel < 3; channel++)
        {
            s16 polarity;

            /* If freqdiv is 0 or 1 the channel output is always 1 */
            if (freqDiv_[channel] <= 1) channel_output_[channel] = 1;

            if (channel_output_[channel]) polarity = 1;
            else polarity = -1;

            snd += polarity * volume_table[volume_[channel]];
        }

        /* Now, generate samples for Noise generator. */
        if (channel_output_[3] == 1)
        {
            snd += volume_table[volume_[3]];
        }

        /*if (!Fifo_->write ( snd / 2)) return false; is better. No saturation.*/
        if (!Fifo_->write ( snd )) return false;
        last_sample_ = snd;
        cycles--;
    }
    return true;
}

/*-------------------------------------------------------------*/
/* Fill the given save state structure for save.               */
/*-------------------------------------------------------------*/
bool SN76489::saveState( ofstream &ofs)
{
    SN76489SaveState s;

    s.lastRegister_ = lastRegister_;     // Last written register
    for (u8 i=0; i < 4; i++) s.volume_[i] = volume_[i];
    for (u8 i=0; i < 4; i++) s.freqDiv_[i] = freqDiv_[i];
    for (u8 i=0; i < 4; i++) s.half_period_[i] = half_period_[i];
    for (u8 i=0; i < 4; i++) s.period_counter_[i] = period_counter_[i];
    s.whiteNoise_ = whiteNoise_;
    s.follow_tone2_frequency_ = follow_tone2_frequency_;

    ofs.write((char *)&s, sizeof(s));
    return ofs.good();
}

/*-------------------------------------------------------------*/
/* Restore state from the given save state structure.          */
/*-------------------------------------------------------------*/
bool SN76489::loadState( ifstream &ifs)
{
    SN76489SaveState s;

    ifs.read((char *)&s, sizeof(s));
    if (!ifs.good()) return false;

    lastRegister_ = s.lastRegister_;     // Last written register
    for (u8 i=0; i < 4; i++) volume_[i] = s.volume_[i];
    for (u8 i=0; i < 4; i++) freqDiv_[i] = s.freqDiv_[i];
    for (u8 i=0; i < 4; i++) half_period_[i] = s.half_period_[i];
    for (u8 i=0; i < 4; i++) period_counter_[i] = s.period_counter_[i];
    whiteNoise_ = s.whiteNoise_;
    follow_tone2_frequency_ = s.follow_tone2_frequency_;
    return true;
}
