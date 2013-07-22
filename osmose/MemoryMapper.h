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
 * File: MemoryMapper.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle emulator read/write and bank
 * switching during emulation.
 *
 * Author: Vedder Bruno
 * Date: 02/10/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "unzip/unzip.h"
#include "Options.h"
#include "Definitions.h"
#include "DebugEventThrower.h"
#include "SaveState.h"
#include "OsmoseConfigurationFile.h"
#include "QLogWindow.h"

extern Options opt;

using namespace std;

enum Mapper
{
    SegaMapper =0,
    CodemasterMapper,
    KoreanMapper
};

/* Enumeration of adressing space areas types that could be read/written. */
enum Area_type
{
    Cartridge,
    Ram,
    SRam,
    Null    // Rom write attemps are redirected to null.
};

/*---------------------------------------------------------------------------*/
/*              Structure to save Memory mapper state.                       */
/* It's necessary to save paging registers, but it's Also required to save   */
/* the bank mapping, instead of doing fake wr8 on adress 0xFFFC-0xFFFF to    */
/* get the correct mapping (order dependant for FFFC). As RAM pointer are    */
/* not identical from different process, we save the area type of memory     */
/* plus the bloc (8Ko) number inside the area.                               */
/* e.g: read_map[0] pointing to cartridge 0x2000 will be saved as :          */
/* rd_area_type = Cartridge,  block_in_rd_area = 1                           */
/*---------------------------------------------------------------------------*/
typedef struct
{
    unsigned char paging_regs[4];       // Paging registers.
    Area_type rd_area_type[8];
    unsigned int block_in_rd_area[8];
    Area_type wr_area_type[8];
    unsigned int block_in_wr_area[8];
    Mapper mapperType;

} MemoryMapperSaveState;



class MemoryMapper : public DebugEventThrower, public ImplementsSaveState
{
    public:

        MemoryMapper(const char *rom_file, OsmoseConfigurationFile *c);
        void save_battery_backed_memory(string f);
        void reset();
        void dump(unsigned char bnk_nbr);
        void dump_page(unsigned char page);
        void dump_mem(unsigned add, unsigned short nb_line);
        void dump_smem(unsigned add, unsigned short nb_line);
        void wr8(unsigned address, unsigned char value);
        unsigned char rd8(unsigned  address);
        unsigned char getRSR();
        unsigned char getFFFD();
        unsigned char getFFFE();
        unsigned char getFFFF();
        string getROMName();
        void setMapperType (Mapper map);

        /* Implemetntation of ImplementsSaveState. */
        bool saveState( ofstream &ofs);
        bool loadState( ifstream &ifs);

    private:

        bool	    	have_bbr;		    // Battery backed ram flag presence
        string 	    	rom_name;		    // Rom name without extension.
        unsigned 	    rom_size;		    // ROM size in bytes
        unsigned        bank_nbr;		    // How much 8k block in our rom
        unsigned        bank16Ko_nbr;	    // How much 16k bank in our rom
        unsigned char   *null_rom;		    // Ptr on Garbage (use for ROM writes).
        unsigned char   *sram;			    // Ptr on Optionnal SRAM
        unsigned char   *ram;			    // Central RAM
        unsigned char   *cartridge;		    // Ptr on ROM cartridge.
        unsigned char   paging_regs[4];     // Paging registers.

        unsigned char   *write_map[8];	    // 8ko bank ptr for CPU writes.
        Area_type wr_area_type[8];          // actual wr_map area type.
        unsigned int block_in_wr_area[8];   // 8ko block inside the area.

        unsigned char   *read_map[8];	    // 8ko bank ptr for CPU reads.
        Area_type rd_area_type[8];          // actual read_map area type.
        unsigned int block_in_rd_area[8];   // 8ko block inside the area.

        bool save_bbr;			// Flag for Battery Backed Memory.
        Mapper mapperType;

        unsigned int LoadZippedRom(const char *rom_file);
        unsigned int LoadSMSRom(const char *rom_file);
        void DumpMappingPtr();
        void wr8_sega_mapper(unsigned int add, unsigned char data);
        void wr8_codemaster_mapper(unsigned int add, unsigned char data);
        void wr8_korean_mapper(unsigned int add, unsigned char data);
        void write_standard_paging_reg(int reg, unsigned char value);
        void write_codemaster_paging_reg(unsigned char value);
        void DisplayROMSize();
        unsigned int getCRC32(unsigned char *buffer, unsigned int len);
        void (MemoryMapper::*wr8_method)(unsigned int add, unsigned char data);
		OsmoseConfigurationFile *configuration;
};
#endif
