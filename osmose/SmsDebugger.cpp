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
 * File: SmsDebugger.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class will handle built-in debugger.
 *
 * Author: Vedder Bruno
 * Date: 16/10/2004, 18h00
 *
 * URL: http://bcz.asterope.fr
 */
 
#include <iostream>
#include <iomanip>
#include "SmsDebugger.h"

/*--------------------------------------------------------------------*/
/* SmsDebugger class constructor.				      */
/*--------------------------------------------------------------------*/
SmsDebugger::SmsDebugger()
{
    end_session = false;
    any_breakpoint = false;
    breakpoint_on_irq = false;
    breakpoint_on_enable_interrupt = false;
    breakpoint_on_disable_interrupt = false;
    clearBreakpoints();
    scanlineBreakpoint = -1;
    cpu_steping = false;
}

/*--------------------------------------------------------------------*/
/* This method is the debugger entry point. It read command line and  */
/* interpret it, and call associated method.						  */
/*--------------------------------------------------------------------*/
void SmsDebugger::enter()
{
    char *line;
    size_t n_byte = 256;
    char cmd[32];
    int param1;
    int param2;
    int param3;

    unsigned char par_nbr;

    while (end_session == false)
    {
        dumpRegisters();
        dasm->disasm(cpu->PC);

        cout << endl << "Cmd:";
        line = (char *) malloc(n_byte+1);
        getline(&line,&n_byte,stdin);
        par_nbr = sscanf(line,"%s %x %x %x", cmd, &param1, &param2, &param3);
        free(line);
        switch (par_nbr)
        {
            case 1:
                exec_cmd( cmd, param1);
                break;

            case 2:
                exec_cmd( cmd, param1, param2);
                break;

            default:

                break;
        }
    }
}

/*--------------------------------------------------------------------*/
/* This method displays help message.				      */
/*--------------------------------------------------------------------*/
void SmsDebugger::help()
{
    cout << "'dpr'         -> Dump Paging Registers." << endl;
    cout << "'dvdpr'       -> Dump VDP registers." << endl;
    cout << "'vdpi'        -> VDP human readable info." << endl;
    cout << "'dcram'       -> Dump VDP Color RAM." << endl;
    cout << "'dvram XXXX'  -> Dump VDP RAM from XXXX."<< endl;
    cout << "'dsram XXXX'  -> Dump SRAM from XXXX."<< endl;
    cout << "'help'        -> This help."     << endl;
    cout << "'quit'        -> Exit emulator." << endl;
    cout << "'c'           -> Exit debugger, until next breakpoint." << endl;
    cout << "'s'           -> Step (execute) one Z80 instruction." << endl;
    cout << "'u [XXXX]'    -> Unassemble 16 instruction from PC or XXXX." << endl;
    cout << "'d [XXXX]'    -> Dump memory from PC or XXXX." << endl;
    cout << "'bp XXXX'     -> Put breakpoint at XXXX." << endl;
    cout << "'cbp'         -> Clear ALL breakpoints." << endl;
    cout << "'lbp'         -> List all breakpoints." << endl;
    cout << "'irqbp'       -> Toggle (ON/OFF) breakpoint on IRQ." << endl;
    cout << "'slbp [XX]'   -> Breakpoint on scanline XX. Set negative value to remove breakpoint. use slbp witout value to show scanline breakpoint." << endl;
    cout << "'bpdi'        -> Breakpoint when CPU exec DI opcode." << endl;
    cout << "'bpei'        -> Breakpoint when CPU exec EI opcode." << endl;
    cout << "* All parameters are expected in hexadecimal values."<< endl;
}

/*--------------------------------------------------------------------*/
/* This method displays paging registers FFFC-FFFF.		      */
/*--------------------------------------------------------------------*/
void SmsDebugger::dpr()
{
    unsigned char l_rsr;
    string state;
    l_rsr = mem->getRSR();
    if (l_rsr & 0x8)
    {
        if (l_rsr & 0x4)
        {
            state = " [0x8000-0xBFFF is opt RAM bank 2]";
        }
        else
        {
            state = " [0x8000-0xBFFF is opt RAM bank 1]";
        }
    }
    else
    {
        state = " [0x8000-0xBFFF is ROM mapped as 0xFFFF]";
    }
    cout << "FFFC (RSR)                 = 0x" << hex << setw(2) << setfill('0') << (int)l_rsr << state << endl;
    cout << "FFFD (PAGE0) 0x0000-0x3FFF = 0x" << hex << setw(2) << setfill('0') << (int)mem->getFFFD() << endl;
    cout << "FFFE (PAGE1) 0x4000-0x7FFF = 0x" << hex << setw(2) << setfill('0') << (int)mem->getFFFE() << endl;
    cout << "FFFF (PAGE2) 0x8000-0xBFFF = 0x" << hex << setw(2) << setfill('0') << (int)mem->getFFFF() << endl;
}

/*--------------------------------------------------------------------*/
/* This method displays VDP registers.				      */
/*--------------------------------------------------------------------*/
void SmsDebugger::dvdpr()
{
    for (int i=0;i<VDP_REGISTER_NBR;i++)
    {
        cout << "R["<< dec << setw(2) << setfill('0')<< i<<"]=" << hex << setw(2) << setfill('0') << (int)v->regs[i]<<"  ";
        if (i == 7) cout << endl;
    }
    cout << endl;
    cout << "vdp_status=" << hex << setw(2) << setfill('0') << (int)v->vdp_status;
    cout << " Drawing line " << dec << setw(3) << setfill('0') << (int)v->line << endl;
}

/*--------------------------------------------------------------------*/
/* This method displays human readable VDP info.      	 	      */
/*--------------------------------------------------------------------*/
void SmsDebugger::vdpi()
{
    cout << "* VDP Register 0:" << endl;
    if (v->REG0 & BIT7)
    {
        cout << "Reg0:b7 -> Disable vertical scrolling for columns 24-31." << endl;
    }
    else
    {
        cout << "Reg0:b7 -> Enable vertical scrolling for columns 24-31." << endl;
    }
    if (v->REG0 & BIT6)
    {
        cout << "Reg0:b6 -> Disable horizontal scrolling for rows 0-1." << endl;
    }
    else
    {
        cout << "Reg0:b6 -> Enable horizontal scrolling for rows 0-1." << endl;
    }
    if (v->REG0 & BIT5)
    {
        cout << "Reg0:b5 -> Mask column 0 with overscan color from register #7." << endl;
    }
    else
    {
        cout << "Reg0:b5 -> Do not mask column 0 with overscan color from register #7." << endl;
    }

    if (v->REG0 & BIT4)
    {
        cout << "Reg0:b4 -> Line interrupt is enabled." << endl;
    }
    else
    {
        cout << "Reg0:b4 -> Line interrupt is disabled." << endl;
    }

    if (v->REG0 & BIT3)
    {
        cout << "Reg0:b3 -> Shift sprites left by 8 pixels." << endl;
    }
    else
    {
        cout << "Reg0:b3 -> Do not shift sprites left by 8 pixels." << endl;
    }
    if (v->REG0 & BIT2)
    {
        cout << "Reg0:b2 -> 1 (Use Mode 4)" << endl;
    }
    else
    {
        cout << "Reg0:b2 -> 0 (Do not use mode 4, Use TMS9918 modes (selected with M1, M2, M3." << endl;
    }
    if (v->REG0 & BIT1)
    {
        cout << "Reg0:b1 -> 1 (Must be 1 for M1/M3 to change screen height in Mode 4)." << endl;
    }
    else
    {
        cout << "Reg0:b1 -> 0 (Must be 1 for M1/M3 to change screen height in Mode 4)." << endl;
    }
    if (v->REG0 & BIT0)
    {
        cout << "Reg0:b0 -> No sync, display is monochrome." << endl;
    }
    else
    {
        cout << "Reg0:b0 -> Sync, normal display." << endl;
    }


    cout << "* VDP Register 1:" << endl;
    if (v->REG1 & BIT7)
    {
        cout << "Reg1:b7 -> 1, Unused." << endl;
    }
    else
    {
        cout << "Reg1:b7 -> 0, Unused." << endl;
    }
    if (v->REG1 & BIT6)
    {
        cout << "Reg1:b6 -> Display enabled." << endl;
    }
    else
    {
        cout << "Reg1:b6 -> Display disabled." << endl;
    }
    if (v->REG1 & BIT5)
    {
        cout << "Reg1:b5 -> Frame interrupt enabled." << endl;
    }
    else
    {
        cout << "Reg1:b5 -> Frame interrupt disabled." << endl;
    }

    if (v->REG1 & BIT4)
    {
        cout << "Reg1:b4 -> 1, (if 1, Selects 224-line screen for Mode 4 if M2=1)." << endl;
    }
    else
    {
        cout << "Reg1:b4 -> 0, (if 1, Selects 224-line screen for Mode 4 if M2=1)." << endl;
    }

    if (v->REG1 & BIT3)
    {
        cout << "Reg1:b3 -> 1, (if 1, Selects 240-line screen for Mode 4 if M2=1)." << endl;
    }
    else
    {
        cout << "Reg1:b3 -> 0, (if 1, Selects 240-line screen for Mode 4 if M2=1)." << endl;
    }
    if (v->REG1 & BIT2)
    {
        cout << "Reg1:b2 -> 1, Unused." << endl;
    }
    else
    {
        cout << "Reg1:b2 -> 0, Unused." << endl;
    }
    if (v->REG1 & BIT1)
    {
        cout << "Reg1:b1 -> 1, Sprites are 16x16,(TMS9918), Sprites are 8x16, (Mode 4)." << endl;
    }
    else
    {
        cout << "Reg1:b1 -> 0 Sprites 8x8 (TMS9918), Sprites are 8x8 (Mode 4)." << endl;
    }
    if (v->REG1 & BIT0)
    {
        cout << "Reg1:b0 -> Sprite pixels are doubled in size." << endl;
    }
    else
    {
        cout << "Reg1:b0 -> Sprite pixels are NOT doubled in size.." << endl;
    }

    cout << "* VDP Status:" << endl;
    if (v->vdp_status & BIT7)
    {
        cout << "VDP Status:b7 -> 1, Frame interrupt pending." << endl;
    }
    else
    {
        cout << "VDP Status:b7 -> 0, No frame interrupt pending." << endl;
    }

    if (v->getIrqLinePending())
    {
        cout << "VDP :Line IRQ pending." << endl;
    }
    else
    {
        cout << "VDP :No Line IRQ pending." << endl;
    }

    if (v->vdp_status & BIT6)
    {
        cout << "VDP Status:b6 -> 1, Sprite overflow flag is set." << endl;
    }
    else
    {
        cout << "VDP Status:b6 -> 0, Sprite overflow flag is not set." << endl;
    }

    if (v->vdp_status & BIT5)
    {
        cout << "VDP Status:b5 -> 1, Sprite collision flag is set." << endl;
    }
    else
    {
        cout << "VDP Status:b5 -> 0, Sprite collision flag is not set." << endl;
    }
    cout << "Line=" << dec << setw(3) << setfill('0') << (int)v->line ;
    cout << " / VRAM addr=" << hex << setw(4) << setfill('0') << (int)v->getVRAMAddr();
    cout << " / Spr. table=" << hex << setw(4) << setfill('0') << (int)v->sit_addr ;
    cout << " / Tile table=" << hex << (int)v->map_addr << endl;
    cout << "i_counter (REG10) =" << dec << setw(3) << setfill('0') << (int)v->i_counter << endl;
}

/*--------------------------------------------------------------------*/
/* This method displays Z80 registers		.					      */
/*--------------------------------------------------------------------*/
void SmsDebugger::dumpRegisters()
{
    cout << "A=" << hex << setw(2) << setfill('0') << (int)cpu->A;
    cout << "  B=" << hex << setw(2) << setfill('0') << (int)cpu->B;
    cout << "  C=" << hex << setw(2) << setfill('0') << (int)cpu->C;
    cout << "  D=" << hex << setw(2) << setfill('0') << (int)cpu->D;
    cout << "  E=" << hex << setw(2) << setfill('0') << (int)cpu->E;
    cout << "  H=" << hex << setw(2) << setfill('0') << (int)cpu->H;
    cout << "  L=" << hex << setw(2) << setfill('0') << (int)cpu->L;
    cout << "  Flag=" << hex << setw(2) << setfill('0') << (int)cpu->F;
    cout << endl;
    cout << "PC=" << hex << setw(4) << setfill('0') << (int)cpu->PC;
    cout << "  SP=" << hex << setw(4) << setfill('0') << (int)cpu->SP;
    cout << "  IX=" << hex << setw(4) << setfill('0') << (int)cpu->IX;
    cout << "  IY=" << hex << setw(4) << setfill('0') << (int)cpu->IY;
    cout << "  I=" << hex << setw(2) << setfill('0') << (int)cpu->I;
    cout << "  R=" << hex << setw(2) << setfill('0') << (int)cpu->R;

    cout << endl;
}

/*--------------------------------------------------------------------*/
/* This method will remove ALL debugger breakpoints.		      */
/*--------------------------------------------------------------------*/
void SmsDebugger::clearBreakpoints()
{
    /* Set break point to unused value */
    for (int i=0;i<MAX_BREAKPOINTS; i++)
    {
        breakpoints[i] = -1;
        bp_index = 0;
        any_breakpoint = false;
    }
}

/*--------------------------------------------------------------------*/
/* This method will add a debugger breakpoints. If the breakpoints    */
/* number is > MAX_BREAKPOINTS, the first breakpoint will be 	      */
/* overwritten. This is a circular buffer.			      */
/*--------------------------------------------------------------------*/
void SmsDebugger::addBreakpoint(int ad)
{
    if (ad >0xFFFF)
    {
        cout << "Breakpoint address is out of range."<< endl;
        return;
    }
    breakpoints[bp_index] = ad;
    any_breakpoint = true;
    bp_index++;
    if (bp_index>=MAX_BREAKPOINTS)
    {
        bp_index = 0;
    }
    cout << "Breakpoint added at address "<< hex << setw(4) << setfill('0') << ad <<"."<< endl;
}

/*--------------------------------------------------------------------*/
/* This method will list all debugger breakpoints.		      */
/*--------------------------------------------------------------------*/
void SmsDebugger::listBreakpoints()
{
    int nb =0;

    if (any_breakpoint)
    {
        for (int i=0;i<MAX_BREAKPOINTS; i++)
        {
            if (breakpoints[i] != -1)
            {
                cout << "Breakpoint at address "<< hex << setw(4) << setfill('0') << breakpoints[i] <<"."<< endl;
                nb++;
            }
        }
    }
    else
    {
        cout << "No Breakpoints found."<< endl;
    }
}

/*--------------------------------------------------------------------*/
/* This method exec a command with one parameter.					  */
/*--------------------------------------------------------------------*/
void SmsDebugger::exec_cmd(char *cmd, int param1)
{
    end_session = false;
    if (strcmp(cmd,"quit")==0 )
    {
        cout << "Exiting Osmose." << endl;
        exit(0);
    }
    if (strcmp(cmd,"irqbp")==0 )
    {
        breakpoint_on_irq ^= 1;
        if (breakpoint_on_irq) cout << "Breakpoint on IRQ ON." << endl;
        else cout << "Breakpoint on IRQ OFF." << endl;
        return;
    }
    if (strcmp(cmd,"help")==0 )
    {
        help();
        return;
    }
    if (strcmp(cmd,"c")==0 )
    {
        end_session = true;
        return;
    }
    if (strcmp(cmd,"dpr")==0 )
    {
        dpr();
        return;
    }
    if (strcmp(cmd,"dvdpr")==0 )
    {
        dvdpr();
        return;
    }

    if (strcmp(cmd,"vdpi")==0 )
    {
        vdpi();
        return;
    }

    if (strcmp(cmd,"cbp")==0 )
    {
        clearBreakpoints();
        cout << "Breakpoints cleared." << endl;
        return;
    }
    if (strcmp(cmd,"dcram")==0 )
    {
        v->dumpCRAM();
        return;
    }

    if (strcmp(cmd,"s")==0 )
    {
        /* Trace one instruction */
        cpu_steping = true;
        end_session = true;
        return;
    }
    if (strcmp(cmd,"lbp")==0 )
    {
        listBreakpoints();
        return;
    }

    if (strcmp(cmd,"slbp")==0 )
    {
        cout << "Scanline breakpoint on scanline : 0x" << hex << scanlineBreakpoint << "." << endl;
        return;
    }

    if (strcmp(cmd,"u")==0 )
    {
        /* unassemble 16 instructions from PC. */
        param1 = cpu->PC;
        for (int i=0;i<16;i++)
        {
            param1 = dasm->disasm(param1);
        }
        printf("\n");
        return;
    }
    /* Dump 16 block of 16 bytes memory from PC. */
    if (strcmp(cmd,"d")==0 )
    {
        mem->dump_mem(cpu->PC, 16);
        return;
    }

    if (strcmp(cmd,"bpdi")==0 )
    {
        breakpoint_on_disable_interrupt ^= 1;
        if (breakpoint_on_disable_interrupt) cout << "Breakpoints when CPU exec DI: ON" << endl;
        else cout << "Breakpoints when CPU exec DI: OFF" << endl;
        return;
    }

    if (strcmp(cmd,"bpei")==0 )
    {
        breakpoint_on_enable_interrupt ^= 1;
        if (breakpoint_on_enable_interrupt) cout << "Breakpoints when CPU exec EI: ON" << endl;
        else cout << "Breakpoints when CPU exec EI: OFF" << endl;
        return;
    }


    unknownCommand();
}

/*--------------------------------------------------------------------*/
/* This method exec a command with two parameters.					  */
/*--------------------------------------------------------------------*/
void SmsDebugger::exec_cmd(char *cmd, int param1, int  param2)
{
    if (strcmp(cmd,"u")==0 )
    {
        /* unassemble 16 instructions */
        for (int i=0;i<16;i++)
        {
            param1 = dasm->disasm(param1);
        }
        printf("\n");
        return;
    }
    if (strcmp(cmd,"d")==0 )
    {
        mem->dump_mem(param1, 16);
        return;
    }

    if (strcmp(cmd,"dsram")==0 )
    {
        mem->dump_smem(param1, 16);
        return;
    }

    if (strcmp(cmd,"dvram")==0 )
    {
        v->dumpVRAM(param1, 16);
        return;
    }
    if (strcmp(cmd,"bp")==0 )
    {
        addBreakpoint(param1);
        return;
    }

    if (strcmp(cmd,"slbp")==0 )
    {
        setScanlineBreakpoint(param1);
        return;
    }

    unknownCommand();
    return;
}

void SmsDebugger::unknownCommand()
{
    cout << "Unkown command." << endl;
}

void SmsDebugger::setScanlineBreakpoint(int scanline)
{
    scanlineBreakpoint = scanline;
    cout << "Set Breakpoint on scanline " << dec << scanlineBreakpoint << endl;
}

/*--------------------------------------------------------------------*/
/* DebugEventListener interface implementation.						  */
/*--------------------------------------------------------------------*/
void SmsDebugger::sendDebugEvent(int event_type, char *source, char *message)
{
    /* Display debugEvent message.  */

    switch (event_type)
    {
        case DbgEvtCpuStep:
            if (cpu_steping || !end_session)
            {
                cpu_steping = false;
                end_session = false;
                enter();
            }
            else
            {
                if (any_breakpoint)
                {
                    for (int i=0;i<MAX_BREAKPOINTS; i++)
                    {
                        if ( breakpoints[i] == (int)cpu->PC )
                        {
                            end_session = false;
                            cout <<"Reach Breakpoint at :" << hex << cpu->PC << endl;
                            enter();
                        }
                    }
                }
            }
            break;

        case DbgEvtUserTrigger:
            cout << "DBG EVT from " << source <<" : " << message << endl;
            end_session = false;
            enter();
            break;

        case DbgEvtScanlineBreakpoint:
            /* Check scanline breakpoint.*/
            if (v->line == scanlineBreakpoint)
            {
                cout << "DBG EVT from " << source <<" : " << message << endl;
                end_session = false;
                enter();
            }
            break;

        case DbgEvtCpuIrqAsserted:
            if (breakpoint_on_irq)
            {
                cout << "DBG EVT from " << source <<" : " << message << endl;
                end_session = false;
                enter();
            }
            break;

        case DbgEvtCpuDisableInterrupt:
            if (breakpoint_on_disable_interrupt)
            {
                cout << "DBG EVT from " << source <<" : " << message << endl;
                end_session = false;
                enter();
            }
            break;

        case DbgEvtCpuEnableInterrupt:
            if (breakpoint_on_enable_interrupt)
            {
                cout << "DBG EVT from " << source <<" : " << message << endl;
                end_session = false;
                enter();
            }
            break;

        case DbgEvtGeneric:
            cout << "DBG EVT from " << source <<" : " << message << endl;
            end_session = false;
            enter();
            break;


        default:
            cout << "UNKNOWN DBG EVT from " << source <<" : " << message << endl;
            end_session = false;
            break;
    }
}
