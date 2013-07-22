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
 * File: MemoryMapper.cpp
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
 
#include "MemoryMapper.h"
#include "Options.h"
#include "RomSpecificOption.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "AnsiColorTerminal.h"

extern Options opt;

/*--------------------------------------------------------------------*/
/* Class constructor. It immediatly load a given rom, and updates     */
/* Memory mapper variables.					      */
/*--------------------------------------------------------------------*/
MemoryMapper::MemoryMapper(const char *rom_file, OsmoseConfigurationFile *conf)
{
	configuration = conf;
    save_bbr       = false;
    string n = string(rom_file);
    string ext;
    int last_separator_index = -1;
    unsigned int rom_crc;

    if (n.length() >=5)
    {
        ext = n.substr(n.length()-3,3);
    }
    else
    {
		string error_message = "Invalid ROM name.\nValid name is at least one letter, and extension. Ex: a.sms or b.zip";
        throw error_message;
    }

    // Load SMS unzipped file.
    if (ext == "sms" || ext == "SMS")
    {
        rom_crc = LoadSMSRom(rom_file);
		string msg = "Switching emulator to SMS mode.";
		QLogWindow::getInstance()->appendLog(msg);
    }
    else
        if (ext == ".gg" || ext == ".GG") // Load GAMEGEAR unzipped file.
        {
            rom_crc = LoadSMSRom(rom_file);
            opt.MachineType = GAMEGEAR;
			string msg = "Switching emulator to GAMEGEAR mode.";
			QLogWindow::getInstance()->appendLog(msg);
        }
        else
            if (ext == "zip" || ext == "ZIP")
            {
                rom_crc = LoadZippedRom(rom_file);
            }
            else
            {
				string error_message = "Unknown file extension:" + ext + ". \nKnown extensions supported by Osmose are: .sms .gg or .zip";
				throw error_message;				
            }

    /* Print the ROM CRC. */
    //cout << "CRC32 = 0x"<< hex << setfill('0') << setw(8) << rom_crc << endl;

    /* Now check in RomSpecificDataBase if we need specific option to run the rom. */
    SpecificRomOptionDatabase::getOptions( rom_crc, &opt );

    // Now extract the rom name.
    for (unsigned int i=0; i < n.length(); i++)
    {
        if (n[i] == '\\' || n[i] == '/')
        {
            last_separator_index =i;
        }
    }

    int ext_lenght = 4;
    if (opt.MachineType == GAMEGEAR) ext_lenght = 3;
    rom_name = n.substr(last_separator_index+1, n.length() - (last_separator_index+1) - ext_lenght);

    // Allocate Central RAM (0xC000-0xDFFF mirrored)
    ram = new unsigned char[0x2000];

	// Clear this RAM.
	for (int i=0; i<0x2000; i++)
	{
		ram[i] = 0;
	}
   

    // Allocate 32Ko RAM banks, (2*16 opt banks) for games that use it.
    sram = new unsigned char[0x8000];

	bool restored_old_bbr = false;

	// Are there any battery backed memory save ?
	ostringstream oss;
	oss << configuration->getBBRPath() << "/" << rom_name << ".bbr";

	ifstream file(oss.str().c_str(), ios::in | ios::binary);
	if (file.is_open() == true )
	{
		// Now load 2*16Ko banks.
		file.read((char *)sram,0x8000);
		file.close();
		restored_old_bbr = true;
		string msg ="Restored Battery Backed Ram (.bbr) file:"+ oss.str();
		QLogWindow::getInstance()->appendLog(msg);
	}

	if (restored_old_bbr != true)
	{
		// No battery backed memory, clear this Optional RAM.
		for (int i=0; i<0x8000; i++)
		{
			sram[i] = 0x0;
		}
	}
    
    //dump_smem(0, 16*20);
    // Allocate 8Ko of ram for writes in rom.
    null_rom = new unsigned char[0x2000];

    /* Init wr8_method pointer on default sega mapper. */
    wr8_method = &MemoryMapper::wr8_sega_mapper;
    mapperType = SegaMapper;

    /* Rom is loaded, reset the MemoryMapper. */
    reset();
}

/*------------------------------------------------------------*/
/* This method reset paging to it's supposed initial value:   */
/* page 0 on first rom bank, page1 on bank1 and so on.	      */
/*------------------------------------------------------------*/
void MemoryMapper::reset()
{

    // Init Read map and Write map.

    read_map[0] = &cartridge[0x0000]; // 0x0000-0x1FFF
    rd_area_type[0] = Cartridge;
    block_in_rd_area[0] = 0;

    read_map[1] = &cartridge[0x2000]; // 0x2000-0x3FFF
    rd_area_type[1] = Cartridge;
    block_in_rd_area[1] = 1;

    read_map[2] = &cartridge[0x4000]; // 0x4000-0x5FFF
    rd_area_type[2] = Cartridge;
    block_in_rd_area[2] = 2;

    read_map[3] = &cartridge[0x6000]; // 0x6000-0x7FFF
    rd_area_type[3] = Cartridge;
    block_in_rd_area[3] = 3;

    read_map[4] = &cartridge[0x8000]; // 0x8000-0x9FFF
    rd_area_type[4] = Cartridge;
    block_in_rd_area[4] = 4;

    read_map[5] = &cartridge[0xA000]; // 0xA000-0xBFFF
    rd_area_type[5] = Cartridge;
    block_in_rd_area[5] = 5;

    read_map[6] = &ram[0];      // 0xC000-0xDFFF
    rd_area_type[6] = Ram;
    block_in_rd_area[6] = 0;

    read_map[7] = &ram[0];      // 0xE000-0xFFFF mirror of 0xC000-0xDFFF
    rd_area_type[7] = Ram;
    block_in_rd_area[7] = 0;

    write_map[0] = &null_rom[0]; // 0x0000-0x1FFF
    wr_area_type[0] = Null;
    block_in_wr_area[0] = 0;

    write_map[1] = &null_rom[0]; // 0x2000-0x3FFF
    wr_area_type[1] = Null;
    block_in_wr_area[1] = 0;

    write_map[2] = &null_rom[0]; // 0x4000-0x5FFF
    wr_area_type[2] = Null;
    block_in_wr_area[2] = 0;

    write_map[3] = &null_rom[0]; // 0x6000-0x7FFF
    wr_area_type[3] = Null;
    block_in_wr_area[3] = 0;

    write_map[4] = &null_rom[0]; // 0x8000-0x9FFF
    wr_area_type[4] = Null;
    block_in_wr_area[4] = 0;

    write_map[5] = &null_rom[0]; // 0xA000-0xBFFF
    wr_area_type[5] = Null;
    block_in_wr_area[5] = 0;

    write_map[6] = &ram[0];	 // 0xC000-0xDFFF
    wr_area_type[6] = Ram;
    block_in_wr_area[6] = 0;

    write_map[7] = &ram[0];	 // 0xE000-0xFFFF mirror of 0xC000-0xDFFF
    wr_area_type[7] = Ram;
    block_in_wr_area[7] = 0;

    // Init pagin registers From FFFC-FFFF.
    paging_regs[0]  = 0;
    paging_regs[1]  = 0;
    paging_regs[2]  = 1;
    paging_regs[3]  = 2;
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function. 		      */
/* Note that this method will dump banks without any banking  */
/* purpose. It's not affected by paging. To dump paged bank   */
/* use dump_page method.				      */
/*------------------------------------------------------------*/
void MemoryMapper::dump(unsigned char bank_n)
{

    int adress = 0;
    if (bank_n >= bank_nbr)
    {
        cout << "Warning, cannot dump bank " << bank_n << " This bank does not exists." << endl;
        return;
    }

    cout << "***Dumping rom bank[" << (int)bank_n << "] (File offset is 0x" << hex << setw(8) << setfill('0') << (bank_n * 16384) << ")." << endl;
    for (int i=0; i<1024; i++)
    {
        cout << hex << setw(4) << setfill('0') << (i*16)  << ": ";
        for (int o=0;o<16;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) read_map[bank_n][adress++] << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function. 		      */
/* Note that this method will dump banks with banking purpose.*/
/* It dumps data mapped into pages.			      */
/*------------------------------------------------------------*/
void MemoryMapper::dump_page(unsigned char bank_n)
{
    int adress = 0;
    if (bank_n > 2)
    {
        cout << "Warning, cannot dump page " << bank_n << " This page does not exists." << endl;
        return;
    }

    cout << "Dumping rom page " << (int)bank_n << endl;
    for (int i=0; i<1024; i++)
    {
        cout << hex << setw(4) << setfill('0') << (i*16)  << ": ";
        for (int o=0;o<8;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) read_map[bank_n][adress++] << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function. 		      */
/* Note that this method will memory using env rd functions.  */
/*------------------------------------------------------------*/
void MemoryMapper::dump_mem(unsigned add, unsigned short nb_line)
{
    for (int i=0; i<nb_line; i++)
    {
        // Write address
        cout << hex << setw(4) << setfill('0') << ((add + i*16)& 0xFFFF)  << ": ";
        for (int o=0;o<16;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) rd8( (add+i*16+o) & 0xFFFF) << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This is a debugging purpose function. 		      */
/* Note that this method will memory using env rd functions.  */
/*------------------------------------------------------------*/
void MemoryMapper::dump_smem(unsigned add, unsigned short nb_line)
{
    add &=0x7fff;
    for (int i=0; i<nb_line; i++)
    {
        // Write address
        cout << hex << setw(4) << setfill('0') << ((add + i*16)& 0xFFFF)  << ": ";
        for (int o=0;o<16;o++)
        {
            cout << hex << setw(2) << setfill('0') <<(int) sram[(add+i*16+o) & 0x7FFF] << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------*/
/* This method wraps write to the selected wr8 method         */
/* The pointer must be initialised with setMemoryMapper		  */
/* to use non default mapper.								  */
/*------------------------------------------------------------*/
void MemoryMapper::wr8(unsigned address, unsigned char value)
{
    (this->*wr8_method)( address, value);
}

/*------------------------------------------------------------*/
/* This method handle every write operations done by the CPU  */
/* accordingly to korean memory mapper.						  */
/* It handles bank switching, RAM/ROM writes.  	              */
/*							                                  */
/* Note that address is already anded with 0xFFFF	          */
/*------------------------------------------------------------*/
void MemoryMapper::wr8_sega_mapper(unsigned address, unsigned char value)
{
    int bnk = (address >> 13);
    write_map[bnk][address & 0x1FFF] = value;
    if (address >= 0xFFFC)
    {
        write_standard_paging_reg(address & 3, value);
    }
}


/*------------------------------------------------------------*/
/* This method handle every write operations done by the CPU  */
/* accordingly to codeemaster memory mapper.				  */
/* It handles bank switching, RAM/ROM writes.  	              */
/* write at 0x8000 changes rom banking.                        */
/*							                                  */
/* Note that address is already anded with 0xFFFF	          */
/*------------------------------------------------------------*/
void MemoryMapper::wr8_codemaster_mapper(unsigned address, unsigned char value)
{
    int bnk = (address >> 13);
    if (address != 0x8000)
    {
        write_map[bnk][address & 0x1FFF] = value;
    }
    else
    {
        write_codemaster_paging_reg(value);
    }
}

/*------------------------------------------------------------*/
/* This method handle every write operations done by the CPU  */
/* accordingly to korean memory mapper.				  */
/* It handles bank switching, RAM/ROM writes.  	              */
/* write at 0xA000 changes rom banking page 2.                */
/*							                                  */
/* Note that address is already anded with 0xFFFF	          */
/*------------------------------------------------------------*/
void MemoryMapper::wr8_korean_mapper(unsigned address, unsigned char value)
{
    int bnk = (address >> 13);
    if (address != 0xA000)
    {
        write_map[bnk][address & 0x1FFF] = value;
    }
    else
    {
        int page = value % bank16Ko_nbr;

        /* Keep copy of 0xA000 paging reg, swap banks.*/
        paging_regs[0] = value;

        read_map[4] = &cartridge[(page<<14)];
        rd_area_type[4] = Cartridge;
        block_in_rd_area[4] = page * 2;

        read_map[5] = &cartridge[(page<<14)+0x2000];
        rd_area_type[5] = Cartridge;
        block_in_rd_area[5] = page * 2 + 1;

        write_map[4] = null_rom;
        wr_area_type[4] = Null;
        block_in_wr_area[4] = 0;

        write_map[5] = null_rom;
        wr_area_type[5] = Null;
        block_in_wr_area[5] = 0;
    }
}


/*------------------------------------------------------------*/
/* This method handle every read operations done by the CPU.  */
/* It handles bank switching, RAM/ROM reads.  	              */
/* Note that address is already anded with 0xFFFF	      */
/*------------------------------------------------------------*/
unsigned char MemoryMapper::rd8(unsigned  address)
{
    unsigned char r=0;
    int bnk = address>> 13; 		// bnk is 0-7.

    if (address < 0x400)
    {
        r = cartridge[address & 0x1FFF];
    }
    else
    {
        r = read_map[bnk][address & 0x1FFF];
    }
    return r;
}


/*------------------------------------------------------------*/
/* This method is in charge of memory mapping.  	      */
/* reg is the mapping register from FFFC-FFFF		      */
/* Value is the value written to this register.		      */
/*------------------------------------------------------------*/
void MemoryMapper::write_standard_paging_reg(int reg, unsigned char value)
{
    int page;
    page = (value % bank16Ko_nbr);
    paging_regs[reg] = value;	// Save paging registers.

    switch (reg)
    {
            // 0xFFFC is written.
        case 0:
            if (value & 8) // If true, An additionnal 32 Ko ram is mapped at 0x8000-BFFF
            {
                // If value & bit 4 is true, we map second 16 Bank.
                // else, it's the first.
                save_bbr = true;  // Save flag for BBR.

                read_map[4]  =  &sram[(value & 4) ? 0x4000 : 0x0000];
                rd_area_type[4] = SRam;
                block_in_rd_area[4] = (value & 4) ? 2 : 0;

                read_map[5]  =  &sram[(value & 4) ? 0x6000 : 0x2000];
                rd_area_type[5] = SRam;
                block_in_rd_area[5] = (value & 4) ? 3 : 1;

                write_map[4] =  &sram[(value & 4) ? 0x4000 : 0x0000];
                wr_area_type[4] = SRam;
                block_in_wr_area[4] = (value & 4) ? 2 : 0;

                write_map[5] =  &sram[(value & 4) ? 0x6000 : 0x2000];
                wr_area_type[5] = SRam;
                block_in_wr_area[5] = (value & 4) ? 3 : 1;
            }
            else
            {
                // We are mapping rom from 0xFFFF register.
                int bloc = paging_regs[3] % bank16Ko_nbr;

                read_map[4]  = &cartridge[(bloc << 14) + 0x0000];
                rd_area_type[4] = Cartridge;
                block_in_rd_area[4] = bloc *2;

                read_map[5]  = &cartridge[(bloc << 14) + 0x2000];
                rd_area_type[5] = Cartridge;
                block_in_rd_area[5] = bloc *2 + 1;

                write_map[4] = null_rom;
                wr_area_type[4] = Null;
                block_in_wr_area[4] = 0;

                write_map[5] = null_rom;
                wr_area_type[5] = Null;
                block_in_wr_area[5] = 0;
            }
            break;

            // 0xFFFD is written, changing Page 0
        case 1:
#ifdef P_VERBOSE
            cout << "Mapping page0 on rom bank " << (unsigned int)(page) << endl;
#endif
            read_map[0] = &cartridge[(page<<14)];
            rd_area_type[0] = Cartridge;
            block_in_rd_area[0] = page *2;


            read_map[1] = &cartridge[(page<<14)+0x2000];
            rd_area_type[1] = Cartridge;
            block_in_rd_area[1] = page *2 +1;
            break;

            // 0xFFFE is written.
        case 2:
#ifdef P_VERBOSE
            cout << "Mapping page1 on rom bank " << (unsigned int)(page) << endl;
#endif
            read_map[2] = &cartridge[(page<<14)];
            rd_area_type[2] = Cartridge;
            block_in_rd_area[2] = page *2;


            read_map[3] = &cartridge[(page<<14)+0x2000];
            rd_area_type[3] = Cartridge;
            block_in_rd_area[3] = page *2 +1;
            break;

            // 0xFFFF is written.
        case 3:

            if (!(paging_regs[0] & 0x08))
            {
#ifdef P_VERBOSE
                cout << "Mapping page2 on rom bank " << (unsigned int)(page) << endl;
#endif
                read_map[4] = &cartridge[(page<<14)];
                rd_area_type[4] = Cartridge;
                block_in_rd_area[4] = page *2;

                read_map[5] = &cartridge[(page<<14)+0x2000];
                rd_area_type[5] = Cartridge;
                block_in_rd_area[5] = page *2 +1;
            }
            break;
    }
}

/*------------------------------------------------------------*/
/* This method is in charge of codemaster memory mapping.     */
/* To use this mapping, emu must be called with -cm option.   */
/* Value is the value written to this register.		      */
/*------------------------------------------------------------*/
void MemoryMapper::write_codemaster_paging_reg(unsigned char value)
{
    int page = value % bank16Ko_nbr;

    /* Keep a copy of 0x8000, swap banks. */
    paging_regs[0] = value;
    read_map[4] = &cartridge[(page<<14)];
    rd_area_type[4] = Cartridge;
    block_in_rd_area[4] = page *2;

    read_map[5] = &cartridge[(page<<14)+0x2000];
    rd_area_type[5] = Cartridge;
    block_in_rd_area[5] = page *2 +1;

    write_map[4] = null_rom;
    wr_area_type[4] = Null;
    block_in_wr_area[4] = 0;

    write_map[5] = null_rom;
    wr_area_type[5] = Null;
    block_in_wr_area[5] = 0;
}

/*------------------------------------------------------------*/
/* This method returns RAM Select Register mapped at 0xFFFC   */
/*------------------------------------------------------------*/
unsigned char MemoryMapper::getRSR()
{
    return paging_regs[0];
}

/*------------------------------------------------------------*/
/* This method returns bank selector apped at 0xFFFD   	      */
/*------------------------------------------------------------*/
unsigned char MemoryMapper::getFFFD()
{
    return paging_regs[1];
}

/*------------------------------------------------------------*/
/* This method returns bank selector apped at 0xFFFE   	      */
/*------------------------------------------------------------*/
unsigned char MemoryMapper::getFFFE()
{
    return paging_regs[2];
}

/*------------------------------------------------------------*/
/* This method returns bank selector apped at 0xFFFF   	      */
/*------------------------------------------------------------*/
unsigned char MemoryMapper::getFFFF()
{
    return paging_regs[3];
}

/*------------------------------------------------------------*/
/* This is a debug method, not used during normal emulation.  */
/*------------------------------------------------------------*/
void MemoryMapper::DumpMappingPtr()
{
//    for (int i=0; i <8;i++)
//    {
//        cout << "readMap[" << i << "]=" << (unsigned)read_map[i] << endl;
//    }
}

/*------------------------------------------------------------*/
/* This method loads Zipped Rom into cartridge memory         */
/*------------------------------------------------------------*/
unsigned int MemoryMapper::LoadZippedRom(const char *rom_file)
{
    unzFile myZip = NULL;
    unz_global_info zip_global_info;
    unz_file_info zip_file_info;
    unsigned char *dummy;		// Used to skip first 512 bytes.
    char filename[256];			// Name of compressed file.
    unsigned int file_nbr = 0;
    int ret;
    bool smsArchiveFound = false;

    // Allocate dummy buffer to skip potential 512 bytes rom header.
    dummy = new unsigned char[512];

    // Open ROM with file pointer at the end of ROM.
    myZip = unzOpen(rom_file);
    if (myZip == NULL)
    {
        string error_msg = "Unable to open " + string(rom_file) + " zip archive.";
        throw error_msg;
    }

    // Get global information on zip.
    ret = unzGetGlobalInfo(myZip, &zip_global_info);
    if (ret == UNZ_OK)
    {
        if (zip_global_info.number_entry != 1)
        {
			string msg ="Warning Found more than one file in archive.";
			QLogWindow::getInstance()->appendLog(msg);
        }
    }
    else
    {
        string error_msg = "unzGetGlobalInfo() call failed.";
        throw error_msg;
    }

    // Get First file in zip archive.
    ret = unzGoToFirstFile(myZip);
    if (ret != UNZ_OK)
    {
        string error_msg = "unzGoToFirstFile() call failed.";
        throw error_msg;		
    }

    do
    {
        // Read global information on the file.
        ret = unzGetCurrentFileInfo(myZip, &zip_file_info,
                                    filename, 256, NULL,0, NULL, 0);
        // Get Sms file original size.
        if (ret == UNZ_OK)
        {
            rom_size = zip_file_info.uncompressed_size;

            // Check Extension: should be .sms .gg .GG or .SMS to be accepted.
            if ((strncasecmp(&filename[strlen(filename)-4],".sms", 4)== 0))
            {
				string msg ="File in zip archive is ";
				msg = msg + filename;
				QLogWindow::getInstance()->appendLog(msg);				
                smsArchiveFound = true;
                opt.MachineType = SMS;
				msg ="Switching emulator to SMS mode.";
				QLogWindow::getInstance()->appendLog(msg);				
            }
            if ((strncasecmp(&filename[strlen(filename)-3],".gg", 3)== 0))
            {
				string msg ="File in zip archive is ";
				msg = msg + filename;
				QLogWindow::getInstance()->appendLog(msg);
                smsArchiveFound = true;
                opt.MachineType = GAMEGEAR;
				msg ="Switching emulator to GAMEGEAR mode.";
				QLogWindow::getInstance()->appendLog(msg);
            }
            file_nbr++;
        }
        else
        {
			string error_msg = "unzGetCurrentFileInfo() call failed.";
			throw error_msg;			
        }

        if (smsArchiveFound != true && file_nbr <  zip_global_info.number_entry)
        {
            ret = unzGoToNextFile (myZip);
            if (ret != UNZ_OK)
            {
				string error_msg = "unzGoToNextFile() call failed.";
				throw error_msg;				
            }
        }

    }
    while (smsArchiveFound == false  &&  file_nbr <  zip_global_info.number_entry);

    if (smsArchiveFound != true)
    {
		string error_msg = "The .zip archive does not contain '.sms' or .'gg' file, aborting.";
		throw error_msg;
    }

    // Now open rom file, prepare for reading.
    ret = unzOpenCurrentFile(myZip);
    if (ret != UNZ_OK)
    {
		string error_msg = "Unable to open file from zip archive.";
		throw error_msg;		
    }

    // Some rom seems to have a 512byte header. Skip it.
    // unzip package doesn't handle seek. So read buffer to skip it.
    if ((rom_size %1024) == 512)
    {
		string msg ="512 bytes ROM header Skipped.";
		QLogWindow::getInstance()->appendLog(msg);
        ret = unzReadCurrentFile(myZip, dummy, 512);
        if (ret < 0)
        {
			string error_msg = "Unable read 512 bytes from zip archive.";
			throw error_msg;	
        }
        rom_size -= 512;
    }

    DisplayROMSize();

    // Save size of rom, in 8Ko bank units.
    bank_nbr = (rom_size / 8192);

    // Get at least 8, 8ko bank to handle all 64ko Z80 memory space.
    if (bank_nbr < 8) bank_nbr = 8;
    bank16Ko_nbr = bank_nbr /2;

	ostringstream oss;
	oss << "Cartdrige contains " << (int)bank16Ko_nbr << " 16Ko banks.";
	QLogWindow::getInstance()->appendLog((char *)oss.str().c_str());
    // Allocate RAM for the whole cartridge.
    if (rom_size < 65536)
    {
        // Allocate at least 64Ko of ROM
        cartridge = new unsigned char[65536];
        memset(cartridge, 0, 65536);
    }
    else
    {
        cartridge = new unsigned char[rom_size];
        memset(cartridge, 0, rom_size);
    }

    // Load rom file.
    ret = unzReadCurrentFile(myZip, cartridge, rom_size);
    if (ret <0)      // ret < 0 mean IO error.
    {
		string error_msg = "Unable to load cartridge from zip archive.";
		throw error_msg;
    }
    
    unzClose(myZip);
    delete []dummy;

    unsigned int crc = getCRC32(cartridge, rom_size);
    return crc;
}


/*------------------------------------------------------------*/
/* This method loads not zipped Rom into cartridge memory.    */
/*------------------------------------------------------------*/
unsigned int MemoryMapper::LoadSMSRom(const char *rom_file)
{
    /* Open ROM with file pointer at the end of ROM. */
    ifstream file(rom_file, ios::in | ios::binary | ios::ate);
    if (file.is_open() == false )
    {
		string error_msg = "Unable to load cartridge from " + string(rom_file) + " archive file.";
		throw error_msg;
    }

    // Get the ROM size.
    rom_size = file.tellg();

    /* Some rom seems to have a 512byte header. Skip it. */
    if ((rom_size %1024) == 512)
    {
		string msg = "512 bytes ROM header Skipped.";
		QLogWindow::getInstance()->appendLog(msg);		
        file.seekg(512, ios::beg);
        rom_size -= 512;
    }
    else
    {
        file.seekg(0, ios::beg);
    }
    DisplayROMSize();

    // Save size of rom, in 8Ko bank units.
    bank_nbr = (rom_size / 8192);

    // Get at least 4 bank to handle all Z80 memory space.
    if (bank_nbr < 8) bank_nbr = 8;
    bank16Ko_nbr = bank_nbr /2;

	ostringstream oss;
	oss << "Cartdrige contains " << (int)bank16Ko_nbr << " 16Ko banks.";
	QLogWindow::getInstance()->appendLog((char *)oss.str().c_str());
	
    // Allocate RAM for the whole cartridge.
    if (rom_size < 65536)
    {
        // Allocate at least 64Ko of ROM
        cartridge = new unsigned char[65536];
        memset(cartridge, 0, 65536);
    }
    else
    {
        cartridge = new unsigned char[rom_size];
        memset(cartridge, 0, rom_size);
    }

    // Now load the ROM.
    file.read((char*)cartridge, rom_size);
    if (file.good()== false)
    {
		string error_msg = "Unable to load .sms file !";
		throw error_msg;
    }
    file.close();

    unsigned int crc = getCRC32(cartridge, rom_size);
    return crc;
}

/*------------------------------------------------------------*/
/* This method displays roms size in mb or kb.		      */
/*------------------------------------------------------------*/
void MemoryMapper::DisplayROMSize()
{
	ostringstream oss;
    
	/* 128 is equivalent (romsize*8)/1024 */
    if ((rom_size/128)> 1024)
    {
		oss << "ROM size is " << rom_size << " bytes (" << ((rom_size*8)/(1024*1024))<< " mbits).";
	}
    else
    {
        oss << "ROM size is " << rom_size << " bytes (" << ((rom_size * 8)/1024)<< " kbits).";
    }
	QLogWindow::getInstance()->appendLog((char *)oss.str().c_str());
}

/*------------------------------------------------------------*/
/* This method return Rom name, based on Rom name, but with   */
/* no extension.					      */
/*------------------------------------------------------------*/
string MemoryMapper::getROMName()
{
    return rom_name;
}

void MemoryMapper::save_battery_backed_memory(string filename)
{
    // If bbr has been written:
    if (save_bbr)
    {
        ofstream file(filename.c_str(), ios::out | ios::binary);
        if (file.is_open() == false )
        {
			string msg = "Unable to create .bbr file !";
			QLogWindow::getInstance()->appendLog(msg);
			return;
        }

        // Now save 2*16Ko banks.
        file.write((const char*)sram,0x8000);
        file.flush();
        file.close();
		string msg = "Battery Backed Ram saved.";
		QLogWindow::getInstance()->appendLog(msg);		
    }
}

/*------------------------------------------------------------*/
/* This method computes CRC32 calculation on an uncompressed  */
/* ROM. It will be use for ROM that need special options, e.g */
/* -cm CodeMaster Mapper ect...								  */
/*------------------------------------------------------------*/
unsigned int MemoryMapper::getCRC32(unsigned char *buffer, unsigned int len)
{
    unsigned int crc32_;
    unsigned long crc_table[256];

    unsigned long c;
    unsigned int n, k;

    for (n = 0; n < 256; n++)
    {
        c = (unsigned long) n;
        for (k = 0; k < 8; k++)
        {
            if (c & 1) c = 0xedb88320L ^ (c >> 1);
            else c = c >> 1;
        }
        crc_table[n] = c;
    }

    crc32_ = 0xFFFFFFFF;
    for (n = 0; n < len; n++)
    {
        crc32_ = crc_table[(crc32_ ^ buffer[n]) & 0xff] ^ (crc32_ >> 8);
    }

    return crc32_;
}

void MemoryMapper::setMapperType(Mapper m)
{
    switch (m)
    {
        case SegaMapper:
            wr8_method = &MemoryMapper::wr8_sega_mapper;
            break;

        case CodemasterMapper:
            wr8_method = &MemoryMapper::wr8_codemaster_mapper;
            break;

        case KoreanMapper:
            wr8_method = &MemoryMapper::wr8_korean_mapper;
            break;
    }

    /* Keep a copy for save states. */
    mapperType = m;
}

/* Implemetntation of ImplementsSaveState. */
bool MemoryMapper::saveState( ofstream &ofs)
{
    MemoryMapperSaveState mss;

    mss.mapperType = mapperType;
    for (int i=0; i < 4; i++) mss.paging_regs[i] = paging_regs[i];

    // Save area types and bloc of the memory mapping for reading.
    for (int i=0; i < 8; i++) mss.rd_area_type[i] = rd_area_type[i];
    for (int i=0; i < 8; i++) mss.block_in_rd_area[i] = block_in_rd_area[i];

    // Save area types and bloc of the memory mapping for writing.
    for (int i=0; i < 8; i++) mss.wr_area_type[i] = wr_area_type[i];
    for (int i=0; i < 8; i++) mss.block_in_wr_area[i] = block_in_wr_area[i];

//    cout << "Saved Mapper Type =" << (unsigned int)mapperType << endl;
//    cout << "Saved paging_regs[0] =" << (unsigned int)paging_regs[0] << endl;
//    cout << "Saved paging_regs[1] =" << (unsigned int)paging_regs[1] << endl;
//    cout << "Saved paging_regs[2] =" << (unsigned int)paging_regs[2] << endl;
//    cout << "Saved paging_regs[3] =" << (unsigned int)paging_regs[3] << endl;

    /* Save 8Ko Ram from 0xC000-0xDFFF. */
    ofs.write((char *)&ram[0], 0x2000);
    if (!ofs.good()) return false;

    /* Save 32Ko Battery Backed Memory. */
    ofs.write((char *)&sram[0], 0x8000);
    if (!ofs.good()) return false;

    /* Save Paging Registers. */
    ofs.write((char *)&mss, sizeof(mss));
    if (!ofs.good()) return false;
    return true;
}

bool MemoryMapper::loadState( ifstream &ifs)
{
    MemoryMapperSaveState mss;

    /* Load 8Ko Ram from 0xC000-0xDFFF. */
    ifs.read((char *)&ram[0], 0x2000);
    if (!ifs.good()) return false;

    /* Load 32Ko Battery Backed Memory. */
    ifs.read((char *)&sram[0], 0x8000);
    if (!ifs.good()) return false;

    /* Load Paging Registers. */
    ifs.read((char *)&mss, sizeof(mss));
    if (!ifs.good()) return false;

    mapperType = mss.mapperType;
    for (int i=0; i < 4; i++) paging_regs[i] = mss.paging_regs[i];

    // Load area types and bloc of the memory mapping for reading.
    for (int i=0; i < 8; i++) rd_area_type[i] = mss.rd_area_type[i];
    for (int i=0; i < 8; i++) block_in_rd_area[i] = mss.block_in_rd_area[i];

    // Load area types and bloc of the memory mapping for writing.
    for (int i=0; i < 8; i++) wr_area_type[i] = mss.wr_area_type[i];
    for (int i=0; i < 8; i++) block_in_wr_area[i] = mss.block_in_wr_area[i];

    // Now rebuild read_maps pointers.
    for (int i=0; i < 8; i++)
    {
        unsigned char *base_ptr = NULL;
        switch (rd_area_type[i])
        {
            case Cartridge:
                base_ptr = cartridge;
                break;

            case Ram:
                base_ptr = ram;
                break;

            case SRam:
                base_ptr = sram;
                break;

            case Null:
                // Everything is readable !
				{
					string msg ="Warning : Wrong area_type for read_map !";
					QLogWindow::getInstance()->appendLog(msg);
                }
				break;

            default:
				{
					string message ="Warning : Unknown area_type for read_map !";
					QLogWindow::getInstance()->appendLog(message);
                }
				break;
        }
        read_map[i] = base_ptr + (block_in_rd_area[i] * 0x2000);
    }

    // Now rebuild write_maps pointers.
    for (int i=0; i < 8; i++)
    {
        unsigned char *base_ptr = NULL;
        switch (wr_area_type[i])
        {
            case Cartridge:
                // Cartridge are read only !
				{
					string msg ="Warning : Wrong area_type for write_map !";
					QLogWindow::getInstance()->appendLog(msg);
                }				
                break;

            case Ram:
                base_ptr = ram;
                break;

            case SRam:
                base_ptr = sram;
                break;

            case Null:
                base_ptr = null_rom;
                break;

            default:
				{
					string msg ="Warning : Unknown area_type for write_map !";
					QLogWindow::getInstance()->appendLog(msg);
                }					
                break;
        }
        write_map[i] = base_ptr + (block_in_wr_area[i] * 0x2000);
    }

//    cout << "Loaded Mapper Type =" << (unsigned int)mapperType << endl;
//    cout << "Loaded paging_regs[0] =" << (unsigned int)paging_regs[0] << endl;
//    cout << "Loaded paging_regs[1] =" << (unsigned int)paging_regs[1] << endl;
//    cout << "Loaded paging_regs[2] =" << (unsigned int)paging_regs[2] << endl;
//    cout << "Loaded paging_regs[3] =" << (unsigned int)paging_regs[3] << endl;
    return true;
}

