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
 * File: Z80.h
 *
 * Project: Osmose emulator.
 *
 * Description: This class defines Z80 cpu emulator. It's table driven, and all
 * opcodes are supported. Not that undocumented flags are not totaly supported.
 *
 *
 * Author: Vedder Bruno
 * Date: 10/01/2006, Thailand, Laos Cambodia :-)
 *
 * URL: http://bcz.asterope.fr
 */

#ifndef Z80_H_
#define Z80_H_
#include "BasicTypes.h"
#include "DebugEventThrower.h"
#include "Definitions.h"
#include "SaveState.h"

// Enable opcode 'hit statistics.'
//#define OPCODES_STATS

/* Flag related constants */
#define     SF 0x80		/* Sign 	*/
#define     ZF 0x40		/* Zero 	*/
#define     YF 0x20		/* Undoc flag 	*/
#define     HF 0x10		/* Half carry 	*/
#define     XF 0x08		/* Undoc flag 	*/
#define     VF 0x04		/* Overflow 	*/
#define     PF 0x04		/* Parity	*/
#define     NF 0x02		/* Add substract*/
#define     CF 0x01		/* Carry 	*/

/* Save state data structure. */
typedef struct
{
    u8 A,F,B,C,D,E,H,L,I,R;     /* Generals registers. 		*/
    u8 A1,F1,B1,C1,D1,E1,H1,L1; /* Alternat ' registers. 	*/
    u8 Rbit7;                   /* Use to store bit 7 of R  */
    u8 IM;                      /* Interrupt mode */
    u16 PC,IX,IY,SP;            /* PC,Stack, indexes registers. 	*/
    bool IFF1,IFF2;             /* NMI/IRQ interrupt flip flop. */
    bool cpuHalted;             /* CPU state vs Halt instruction.*/
    u32 cycleCount;             /* Increase when running CPU. 	 */
} Z80SaveState;


/*
    This class, from Alessandro Scotti (Tickle emulator) Z80environment, must be
    derived, with implementation for each virtual methods. It will be used by Z80 CPU core to
    access RAM/ROM, IO etc...
*/
class Z80Environment
{
    public:
        /* Constructor. */
        Z80Environment()
        {
        }

        /* Destructor. */
        virtual ~Z80Environment()
        {
        }

        /* 8 bits read operation. */
        virtual u8 rd8( u16 )
        {
            return 0xFF;
        }

        /* 8 bits write operation adress, value. */
        virtual void wr8( u16 , u8 )
        {
        }

        /* 16 bits read operation. */
        u16 rd16( u16 addr )
        {
            u8 a,b;
            a = rd8(addr);
            b = rd8((addr+1)& 0xFFFF);
            return ((b<<8) | a);
        }

        /* 16 bits write operation. */
        void wr16( u16 addr, u16 value )
        {
            wr8((addr+1)& 0xFFFF, value >> 8);
            wr8(addr, value & 0xFF);
        }

        /* 8 bits read IO operation. */
        virtual u8 in( u16 )
        {
            return 0xFF;
        }

        /* 8 bits write IO operation adress, value. */
        virtual void out( u16 , u8  )
        {
        }

        /* Called immediately after a RETI is executed. */
        virtual void onReturnFromInterrupt()
        {
        }

        /*
            Called after EI or RETN if interrupts are enabled.
            This function allows the environment to supply a pending interrupt
            if needed.
        */
        virtual void onInterruptsEnabled()
        {
        }
};

class Z80 : public DebugEventThrower, public ImplementsSaveState
{
    public:
        Z80Environment& env;        /* Z80Environment reference. */
        u8 A,F,B,C,D,E,H,L,I,R;     /* Generals registers. 		*/
        u8 A1,F1,B1,C1,D1,E1,H1,L1; /* Alternat ' registers. 	*/
        u8 Rbit7;                   /* Use to store bit 7 of R  */
        u8 IM;                      /* Interrupt mode */
        u16 PC,IX,IY,SP;            /* PC,Stack, indexes registers. 	*/
        u16 IXd, IYd;               /* Used for XY+d adressing mode. */
        bool IFF1,IFF2;             /* NMI/IRQ interrupt flip flop. */
        bool cpuHalted;             /* CPU state vs Halt instruction.*/
        u32 cycleCount;             /* Increase when running CPU. 	 */
        Z80 ( Z80Environment & );   /* Constructor with Z80Environment reference*/
        ~Z80();                     /* Destructor. */
        void reset();               /* Reset Z80.*/
        void nmi();                 /* Generate CPU NMI.*/
        bool interrupt(u8 data);    /* Generate CPU interrupt.*/
        u32 run(u32 cycles);         /* Execute  n cycles. */
        void step();                /* Execute one instruction */
        void setCycles(u32 c)
        {
            cycleCount = c;
        }
        u32 getCycles()
        {
            return cycleCount;
        }
        u8   getInterruptMode()
        {
            return IM;
        }

        /* Implemetntation of ImplementsSaveState. */
        bool saveState( ofstream &ofs);
        bool loadState( ifstream &ifs);


        /*
        * Internal Register Manipulation Functions.
        * Get 16 reg from its 8 bits composant registers.
        */
        u16 getAF()
        {
            return ( (A << 8) | F);
        }
        u16 getBC()
        {
            return ( (B << 8) | C);
        }
        u16 getDE()
        {
            return ( (D << 8) | E);
        }
        u16 getHL()
        {
            return ( (H << 8) | L);
        }
        u16 getIX()
        {
            return ( IX );
        }
        u16 getIY()
        {
            return ( IY );
        }
        u16 getPC()
        {
            return ( PC );
        }
        u16 getSP()
        {
            return ( SP );
        }
        u8  getI()
        {
            return ( I );
        }
        u8  getR()
        {
            return ( R );
        }

#ifdef OPCODES_STATS
        u32 *NO_Prefix;
        u32 *CB_Prefix;
        u32 *DD_Prefix;
        u32 *ED_Prefix;
        u32 *FD_Prefix;
        u32 *DDCB_Prefix;
        u32 *FDCB_Prefix;
        void opcodes_stats();
#endif
    private:

        void dumpSaveStateStructure(Z80SaveState &);    /* For debug purpose.*/
        void dumpValues();                              /* Dump CPU regs etc.*/

        void exec_cb();             /* Execute opcode prefixed 0xCB. */
        void exec_dd();             /* Execute opcode prefixed 0xDD. */
        void exec_ddcb();           /* Execute opcode prefixed 0xDDCB. */
        void exec_ed();             /* Execute opcode prefixed 0xED. */
        void exec_fd();             /* Execute opcode prefixed 0xFD. */
        void exec_fdcb();           /* Execute opcode prefixed 0xFDCB. */
        bool checkInterrupt();
        void dump(u16 addr);

        /*
        * Internal Register Manipulation Functions.
        * Set 8 bits composant registers from 16 bit value.
        */
        void setAF   (u16 v)
        {
            A = v>>8;
            F = v & 0xFF;
        }
        void setBC   (u16 v)
        {
            B = v>>8;
            C = v & 0xFF;
        }
        void setDE   (u16 v)
        {
            D = v>>8;
            E = v & 0xFF;
        }
        void setHL   (u16 v)
        {
            H = v>>8;
            L = v & 0xFF;
        }

        /*
        * Internal indirect  8 bits regs Addressing.
        * Set/Get Indirect 8 bits values.
        */
        u8   getBCi()
        {
            return env.rd8(getBC());    /* read u8 in (BC) */
        }
        void setBCi(u8 val)
        {
            env.wr8(getBC(),val);    /* write u8 in (BC) */
        }
        u8   getDEi()
        {
            return env.rd8(getDE());    /* read u8 in (DE) */
        }
        void setDEi(u8 val)
        {
            env.wr8(getDE(),val);    /* write u8 in (DE) */
        }
        u8   getHLi()
        {
            return env.rd8(getHL());    /* read u8 in (HL) */
        }
        void setHLi(u8 val)
        {
            env.wr8(getHL(),val);    /* write u8 in (HL) */
        }

        /* 8 bit read/write throught (IX+d) and (IY+d). Warning: PC is not incremented !  */
        u8    getIXdi()
        {
            return env.rd8((u16)(IX + (s8)env.rd8(PC)));
        }
        void  setIXdi(u8 val)
        {
            env.wr8((u16)(IX + (s8)env.rd8(PC)),val);
        }
        u8    getIYdi()
        {
            return env.rd8((u16)(IY + (s8)env.rd8(PC)));
        }
        void  setIYdi(u8 val)
        {
            env.wr8((u16)(IY + (s8)env.rd8(PC)),val);
        }
        void  setNNi16(u16 val16b)
        {
            env.wr16(env.rd16(PC),val16b);
        }
        u16   getNNi16()
        {
            return env.rd16(env.rd16(PC));
        }
        void  setNNi8(u8 val8b)
        {
            env.wr8(env.rd16(PC),val8b);
        }
        u8    getNNi8()
        {
            return env.rd8(env.rd16(PC));
        }


        /**
            * Basic Arithmetic CPU Operations:
            */
        u8  inc8(u8 v);         /* increment 8bits value. */
        u8  dec8(u8 v);         /* decrement 8bits value. */
        u8  add8(u8 a,u8 b);    /* add 8 bits values.     */
        u8  adc8(u8 a,u8 b);    /* add with carry 8 bits values.     */
        u8  sbc8(u8 a,u8 b);    /* sub with carry 8 bits values.     */
        u8  sub8(u8 a,u8 b);    /* sub  8 bits values.     */
        u16 add16(u16 a,u16 b); /* add 16 bits values.     */
        void sbcHL(u16 v);      /* SBC HL, REG */
        void adcHL(u16 v);      /* ADC HL, REG */
        void rrd();             /* RRD */
        void rld();             /* RLD */
        void cp8(u8 a, u8 b);   /* Compare 8bits values.   */

        /**
        * Basic Logical CPU Operations:
        */
        u8  and8(u8 a,u8 b);    /* and 8 bits values.     */
        u8  or8(u8 a,u8 b);     /* or 8 bits values.      */
        u8  xor8(u8 a,u8 b);    /* xor 8 bits values.     */

        /**
        * Basic Shift CPU Operations:
        */
        u8 rlc8(u8 v);          /* (<<1) 8 bits value. */
        u8 rrc8(u8 v);          /* (>>1) 8 bits value.*/
        u8 rl8(u8 v);           /* (<<1) 8 bits value.*/
        u8 rr8(u8 v);           /* (>>1) 8 bits value.*/
        u8 sla8(u8 v);          /* .*/
        u8 sra8(u8 v);          /* .*/
        u8 sll8(u8 v);          /* .*/
        u8 srl8(u8 v);          /* .*/

        /**
        * Basic Bit CPU Operations:
        */
        void bit(u8 bit,u8 v);  /* test bit in 8 bits value.*/
        u8   set(u8 bit,u8 v);  /* set bit in 8 bits value.*/
        u8   res(u8 bit,u8 v);  /* reset bit in 8 bits value.*/

        /**
        * Basic Stack CPU Operations:
        */
        u16  pop();              /* Pop 16 bits value.*/
        void push(u16 v);        /* Push 16 bits value*/
        void rst(u16 ea);        /* rst operation.*/
        void setFlagAfterInput(u8 r);
        void invalid_opcode();
        void invalid_prefixed_opcode();
        void nop() ;

        /**
        * CPU opcode callbacks:
        */
        void Opc_std_00();
        void Opc_std_01();
        void Opc_std_02();
        void Opc_std_03();
        void Opc_std_04();
        void Opc_std_05();
        void Opc_std_06();
        void Opc_std_07();
        void Opc_std_08();
        void Opc_std_09();
        void Opc_std_0a();
        void Opc_std_0b();
        void Opc_std_0c();
        void Opc_std_0d();
        void Opc_std_0e();
        void Opc_std_0f();
        void Opc_std_10();
        void Opc_std_11();
        void Opc_std_12();
        void Opc_std_13();
        void Opc_std_14();
        void Opc_std_15();
        void Opc_std_16();
        void Opc_std_17();
        void Opc_std_18();
        void Opc_std_19();
        void Opc_std_1a();
        void Opc_std_1b();
        void Opc_std_1c();
        void Opc_std_1d();
        void Opc_std_1e();
        void Opc_std_1f();
        void Opc_std_20();
        void Opc_std_21();
        void Opc_std_22();
        void Opc_std_23();
        void Opc_std_24();
        void Opc_std_25();
        void Opc_std_26();
        void Opc_std_27();
        void Opc_std_28();
        void Opc_std_29();
        void Opc_std_2a();
        void Opc_std_2b();
        void Opc_std_2c();
        void Opc_std_2d();
        void Opc_std_2e();
        void Opc_std_2f();
        void Opc_std_30();
        void Opc_std_31();
        void Opc_std_32();
        void Opc_std_33();
        void Opc_std_34();
        void Opc_std_35();
        void Opc_std_36();
        void Opc_std_37();
        void Opc_std_38();
        void Opc_std_39();
        void Opc_std_3a();
        void Opc_std_3b();
        void Opc_std_3c();
        void Opc_std_3d();
        void Opc_std_3e();
        void Opc_std_3f();
        void Opc_std_40();
        void Opc_std_41();
        void Opc_std_42();
        void Opc_std_43();
        void Opc_std_44();
        void Opc_std_45();
        void Opc_std_46();
        void Opc_std_47();
        void Opc_std_48();
        void Opc_std_49();
        void Opc_std_4a();
        void Opc_std_4b();
        void Opc_std_4c();
        void Opc_std_4d();
        void Opc_std_4e();
        void Opc_std_4f();
        void Opc_std_50();
        void Opc_std_51();
        void Opc_std_52();
        void Opc_std_53();
        void Opc_std_54();
        void Opc_std_55();
        void Opc_std_56();
        void Opc_std_57();
        void Opc_std_58();
        void Opc_std_59();
        void Opc_std_5a();
        void Opc_std_5b();
        void Opc_std_5c();
        void Opc_std_5d();
        void Opc_std_5e();
        void Opc_std_5f();
        void Opc_std_60();
        void Opc_std_61();
        void Opc_std_62();
        void Opc_std_63();
        void Opc_std_64();
        void Opc_std_65();
        void Opc_std_66();
        void Opc_std_67();
        void Opc_std_68();
        void Opc_std_69();
        void Opc_std_6a();
        void Opc_std_6b();
        void Opc_std_6c();
        void Opc_std_6d();
        void Opc_std_6e();
        void Opc_std_6f();
        void Opc_std_70();
        void Opc_std_71();
        void Opc_std_72();
        void Opc_std_73();
        void Opc_std_74();
        void Opc_std_75();
        void Opc_std_76();
        void Opc_std_77();
        void Opc_std_78();
        void Opc_std_79();
        void Opc_std_7a();
        void Opc_std_7b();
        void Opc_std_7c();
        void Opc_std_7d();
        void Opc_std_7e();
        void Opc_std_7f();
        void Opc_std_80();
        void Opc_std_81();
        void Opc_std_82();
        void Opc_std_83();
        void Opc_std_84();
        void Opc_std_85();
        void Opc_std_86();
        void Opc_std_87();
        void Opc_std_88();
        void Opc_std_89();
        void Opc_std_8a();
        void Opc_std_8b();
        void Opc_std_8c();
        void Opc_std_8d();
        void Opc_std_8e();
        void Opc_std_8f();
        void Opc_std_90();
        void Opc_std_91();
        void Opc_std_92();
        void Opc_std_93();
        void Opc_std_94();
        void Opc_std_95();
        void Opc_std_96();
        void Opc_std_97();
        void Opc_std_98();
        void Opc_std_99();
        void Opc_std_9a();
        void Opc_std_9b();
        void Opc_std_9c();
        void Opc_std_9d();
        void Opc_std_9e();
        void Opc_std_9f();
        void Opc_std_a0();
        void Opc_std_a1();
        void Opc_std_a2();
        void Opc_std_a3();
        void Opc_std_a4();
        void Opc_std_a5();
        void Opc_std_a6();
        void Opc_std_a7();
        void Opc_std_a8();
        void Opc_std_a9();
        void Opc_std_aa();
        void Opc_std_ab();
        void Opc_std_ac();
        void Opc_std_ad();
        void Opc_std_ae();
        void Opc_std_af();
        void Opc_std_b0();
        void Opc_std_b1();
        void Opc_std_b2();
        void Opc_std_b3();
        void Opc_std_b4();
        void Opc_std_b5();
        void Opc_std_b6();
        void Opc_std_b7();
        void Opc_std_b8();
        void Opc_std_b9();
        void Opc_std_ba();
        void Opc_std_bb();
        void Opc_std_bc();
        void Opc_std_bd();
        void Opc_std_be();
        void Opc_std_bf();
        void Opc_std_c0();
        void Opc_std_c1();
        void Opc_std_c2();
        void Opc_std_c3();
        void Opc_std_c4();
        void Opc_std_c5();
        void Opc_std_c6();
        void Opc_std_c7();
        void Opc_std_c8();
        void Opc_std_c9();
        void Opc_std_ca();
        void Opc_std_cb();
        void Opc_std_cc();
        void Opc_std_cd();
        void Opc_std_ce();
        void Opc_std_cf();
        void Opc_std_d0();
        void Opc_std_d1();
        void Opc_std_d2();
        void Opc_std_d3();
        void Opc_std_d4();
        void Opc_std_d5();
        void Opc_std_d6();
        void Opc_std_d7();
        void Opc_std_d8();
        void Opc_std_d9();
        void Opc_std_da();
        void Opc_std_db();
        void Opc_std_dc();
        void Opc_std_dd();
        void Opc_std_de();
        void Opc_std_df();
        void Opc_std_e0();
        void Opc_std_e1();
        void Opc_std_e2();
        void Opc_std_e3();
        void Opc_std_e4();
        void Opc_std_e5();
        void Opc_std_e6();
        void Opc_std_e7();
        void Opc_std_e8();
        void Opc_std_e9();
        void Opc_std_ea();
        void Opc_std_eb();
        void Opc_std_ec();
        void Opc_std_ed();
        void Opc_std_ee();
        void Opc_std_ef();
        void Opc_std_f0();
        void Opc_std_f1();
        void Opc_std_f2();
        void Opc_std_f3();
        void Opc_std_f4();
        void Opc_std_f5();
        void Opc_std_f6();
        void Opc_std_f7();
        void Opc_std_f8();
        void Opc_std_f9();
        void Opc_std_fa();
        void Opc_std_fb();
        void Opc_std_fc();
        void Opc_std_fd();
        void Opc_std_fe();
        void Opc_std_ff();

        // Opcodes CBXX prototypes.
        void Opc_cbxx_00();
        void Opc_cbxx_01();
        void Opc_cbxx_02();
        void Opc_cbxx_03();
        void Opc_cbxx_04();
        void Opc_cbxx_05();
        void Opc_cbxx_06();
        void Opc_cbxx_07();
        void Opc_cbxx_08();
        void Opc_cbxx_09();
        void Opc_cbxx_0a();
        void Opc_cbxx_0b();
        void Opc_cbxx_0c();
        void Opc_cbxx_0d();
        void Opc_cbxx_0e();
        void Opc_cbxx_0f();
        void Opc_cbxx_10();
        void Opc_cbxx_11();
        void Opc_cbxx_12();
        void Opc_cbxx_13();
        void Opc_cbxx_14();
        void Opc_cbxx_15();
        void Opc_cbxx_16();
        void Opc_cbxx_17();
        void Opc_cbxx_18();
        void Opc_cbxx_19();
        void Opc_cbxx_1a();
        void Opc_cbxx_1b();
        void Opc_cbxx_1c();
        void Opc_cbxx_1d();
        void Opc_cbxx_1e();
        void Opc_cbxx_1f();
        void Opc_cbxx_20();
        void Opc_cbxx_21();
        void Opc_cbxx_22();
        void Opc_cbxx_23();
        void Opc_cbxx_24();
        void Opc_cbxx_25();
        void Opc_cbxx_26();
        void Opc_cbxx_27();
        void Opc_cbxx_28();
        void Opc_cbxx_29();
        void Opc_cbxx_2a();
        void Opc_cbxx_2b();
        void Opc_cbxx_2c();
        void Opc_cbxx_2d();
        void Opc_cbxx_2e();
        void Opc_cbxx_2f();
        void Opc_cbxx_30();
        void Opc_cbxx_31();
        void Opc_cbxx_32();
        void Opc_cbxx_33();
        void Opc_cbxx_34();
        void Opc_cbxx_35();
        void Opc_cbxx_36();
        void Opc_cbxx_37();
        void Opc_cbxx_38();
        void Opc_cbxx_39();
        void Opc_cbxx_3a();
        void Opc_cbxx_3b();
        void Opc_cbxx_3c();
        void Opc_cbxx_3d();
        void Opc_cbxx_3e();
        void Opc_cbxx_3f();
        void Opc_cbxx_40();
        void Opc_cbxx_41();
        void Opc_cbxx_42();
        void Opc_cbxx_43();
        void Opc_cbxx_44();
        void Opc_cbxx_45();
        void Opc_cbxx_46();
        void Opc_cbxx_47();
        void Opc_cbxx_48();
        void Opc_cbxx_49();
        void Opc_cbxx_4a();
        void Opc_cbxx_4b();
        void Opc_cbxx_4c();
        void Opc_cbxx_4d();
        void Opc_cbxx_4e();
        void Opc_cbxx_4f();
        void Opc_cbxx_50();
        void Opc_cbxx_51();
        void Opc_cbxx_52();
        void Opc_cbxx_53();
        void Opc_cbxx_54();
        void Opc_cbxx_55();
        void Opc_cbxx_56();
        void Opc_cbxx_57();
        void Opc_cbxx_58();
        void Opc_cbxx_59();
        void Opc_cbxx_5a();
        void Opc_cbxx_5b();
        void Opc_cbxx_5c();
        void Opc_cbxx_5d();
        void Opc_cbxx_5e();
        void Opc_cbxx_5f();
        void Opc_cbxx_60();
        void Opc_cbxx_61();
        void Opc_cbxx_62();
        void Opc_cbxx_63();
        void Opc_cbxx_64();
        void Opc_cbxx_65();
        void Opc_cbxx_66();
        void Opc_cbxx_67();
        void Opc_cbxx_68();
        void Opc_cbxx_69();
        void Opc_cbxx_6a();
        void Opc_cbxx_6b();
        void Opc_cbxx_6c();
        void Opc_cbxx_6d();
        void Opc_cbxx_6e();
        void Opc_cbxx_6f();
        void Opc_cbxx_70();
        void Opc_cbxx_71();
        void Opc_cbxx_72();
        void Opc_cbxx_73();
        void Opc_cbxx_74();
        void Opc_cbxx_75();
        void Opc_cbxx_76();
        void Opc_cbxx_77();
        void Opc_cbxx_78();
        void Opc_cbxx_79();
        void Opc_cbxx_7a();
        void Opc_cbxx_7b();
        void Opc_cbxx_7c();
        void Opc_cbxx_7d();
        void Opc_cbxx_7e();
        void Opc_cbxx_7f();
        void Opc_cbxx_80();
        void Opc_cbxx_81();
        void Opc_cbxx_82();
        void Opc_cbxx_83();
        void Opc_cbxx_84();
        void Opc_cbxx_85();
        void Opc_cbxx_86();
        void Opc_cbxx_87();
        void Opc_cbxx_88();
        void Opc_cbxx_89();
        void Opc_cbxx_8a();
        void Opc_cbxx_8b();
        void Opc_cbxx_8c();
        void Opc_cbxx_8d();
        void Opc_cbxx_8e();
        void Opc_cbxx_8f();
        void Opc_cbxx_90();
        void Opc_cbxx_91();
        void Opc_cbxx_92();
        void Opc_cbxx_93();
        void Opc_cbxx_94();
        void Opc_cbxx_95();
        void Opc_cbxx_96();
        void Opc_cbxx_97();
        void Opc_cbxx_98();
        void Opc_cbxx_99();
        void Opc_cbxx_9a();
        void Opc_cbxx_9b();
        void Opc_cbxx_9c();
        void Opc_cbxx_9d();
        void Opc_cbxx_9e();
        void Opc_cbxx_9f();
        void Opc_cbxx_a0();
        void Opc_cbxx_a1();
        void Opc_cbxx_a2();
        void Opc_cbxx_a3();
        void Opc_cbxx_a4();
        void Opc_cbxx_a5();
        void Opc_cbxx_a6();
        void Opc_cbxx_a7();
        void Opc_cbxx_a8();
        void Opc_cbxx_a9();
        void Opc_cbxx_aa();
        void Opc_cbxx_ab();
        void Opc_cbxx_ac();
        void Opc_cbxx_ad();
        void Opc_cbxx_ae();
        void Opc_cbxx_af();
        void Opc_cbxx_b0();
        void Opc_cbxx_b1();
        void Opc_cbxx_b2();
        void Opc_cbxx_b3();
        void Opc_cbxx_b4();
        void Opc_cbxx_b5();
        void Opc_cbxx_b6();
        void Opc_cbxx_b7();
        void Opc_cbxx_b8();
        void Opc_cbxx_b9();
        void Opc_cbxx_ba();
        void Opc_cbxx_bb();
        void Opc_cbxx_bc();
        void Opc_cbxx_bd();
        void Opc_cbxx_be();
        void Opc_cbxx_bf();
        void Opc_cbxx_c0();
        void Opc_cbxx_c1();
        void Opc_cbxx_c2();
        void Opc_cbxx_c3();
        void Opc_cbxx_c4();
        void Opc_cbxx_c5();
        void Opc_cbxx_c6();
        void Opc_cbxx_c7();
        void Opc_cbxx_c8();
        void Opc_cbxx_c9();
        void Opc_cbxx_ca();
        void Opc_cbxx_cb();
        void Opc_cbxx_cc();
        void Opc_cbxx_cd();
        void Opc_cbxx_ce();
        void Opc_cbxx_cf();
        void Opc_cbxx_d0();
        void Opc_cbxx_d1();
        void Opc_cbxx_d2();
        void Opc_cbxx_d3();
        void Opc_cbxx_d4();
        void Opc_cbxx_d5();
        void Opc_cbxx_d6();
        void Opc_cbxx_d7();
        void Opc_cbxx_d8();
        void Opc_cbxx_d9();
        void Opc_cbxx_da();
        void Opc_cbxx_db();
        void Opc_cbxx_dc();
        void Opc_cbxx_dd();
        void Opc_cbxx_de();
        void Opc_cbxx_df();
        void Opc_cbxx_e0();
        void Opc_cbxx_e1();
        void Opc_cbxx_e2();
        void Opc_cbxx_e3();
        void Opc_cbxx_e4();
        void Opc_cbxx_e5();
        void Opc_cbxx_e6();
        void Opc_cbxx_e7();
        void Opc_cbxx_e8();
        void Opc_cbxx_e9();
        void Opc_cbxx_ea();
        void Opc_cbxx_eb();
        void Opc_cbxx_ec();
        void Opc_cbxx_ed();
        void Opc_cbxx_ee();
        void Opc_cbxx_ef();
        void Opc_cbxx_f0();
        void Opc_cbxx_f1();
        void Opc_cbxx_f2();
        void Opc_cbxx_f3();
        void Opc_cbxx_f4();
        void Opc_cbxx_f5();
        void Opc_cbxx_f6();
        void Opc_cbxx_f7();
        void Opc_cbxx_f8();
        void Opc_cbxx_f9();
        void Opc_cbxx_fa();
        void Opc_cbxx_fb();
        void Opc_cbxx_fc();
        void Opc_cbxx_fd();
        void Opc_cbxx_fe();
        void Opc_cbxx_ff();

        // Opcodes DDXX prototypes.
        void Opc_ddxx_09();
        void Opc_ddxx_19();
        void Opc_ddxx_21();
        void Opc_ddxx_22();
        void Opc_ddxx_23();
        void Opc_ddxx_24();
        void Opc_ddxx_25();
        void Opc_ddxx_26();
        void Opc_ddxx_29();
        void Opc_ddxx_2a();
        void Opc_ddxx_2b();
        void Opc_ddxx_2c();
        void Opc_ddxx_2d();
        void Opc_ddxx_2e();
        void Opc_ddxx_34();
        void Opc_ddxx_35();
        void Opc_ddxx_36();
        void Opc_ddxx_39();
        void Opc_ddxx_44();
        void Opc_ddxx_45();
        void Opc_ddxx_46();
        void Opc_ddxx_4c();
        void Opc_ddxx_4d();
        void Opc_ddxx_4e();
        void Opc_ddxx_54();
        void Opc_ddxx_55();
        void Opc_ddxx_56();
        void Opc_ddxx_5c();
        void Opc_ddxx_5d();
        void Opc_ddxx_5e();
        void Opc_ddxx_60();
        void Opc_ddxx_61();
        void Opc_ddxx_62();
        void Opc_ddxx_63();
        void Opc_ddxx_64();
        void Opc_ddxx_65();
        void Opc_ddxx_66();
        void Opc_ddxx_67();
        void Opc_ddxx_68();
        void Opc_ddxx_69();
        void Opc_ddxx_6a();
        void Opc_ddxx_6b();
        void Opc_ddxx_6c();
        void Opc_ddxx_6d();
        void Opc_ddxx_6e();
        void Opc_ddxx_6f();
        void Opc_ddxx_70();
        void Opc_ddxx_71();
        void Opc_ddxx_72();
        void Opc_ddxx_73();
        void Opc_ddxx_74();
        void Opc_ddxx_75();
        void Opc_ddxx_77();
        void Opc_ddxx_7c();
        void Opc_ddxx_7d();
        void Opc_ddxx_7e();
        void Opc_ddxx_84();
        void Opc_ddxx_85();
        void Opc_ddxx_86();
        void Opc_ddxx_8c();
        void Opc_ddxx_8d();
        void Opc_ddxx_8e();
        void Opc_ddxx_94();
        void Opc_ddxx_95();
        void Opc_ddxx_96();
        void Opc_ddxx_9c();
        void Opc_ddxx_9d();
        void Opc_ddxx_9e();
        void Opc_ddxx_a4();
        void Opc_ddxx_a5();
        void Opc_ddxx_a6();
        void Opc_ddxx_ac();
        void Opc_ddxx_ad();
        void Opc_ddxx_ae();
        void Opc_ddxx_b4();
        void Opc_ddxx_b5();
        void Opc_ddxx_b6();
        void Opc_ddxx_bc();
        void Opc_ddxx_bd();
        void Opc_ddxx_be();
        void Opc_ddxx_e1();
        void Opc_ddxx_e3();
        void Opc_ddxx_e5();
        void Opc_ddxx_e9();
        void Opc_ddxx_f9();

        // Opcodes DDCB prototypes.
        void Opc_ddcb_00();
        void Opc_ddcb_01();
        void Opc_ddcb_02();
        void Opc_ddcb_03();
        void Opc_ddcb_04();
        void Opc_ddcb_05();
        void Opc_ddcb_06();
        void Opc_ddcb_07();
        void Opc_ddcb_08();
        void Opc_ddcb_09();
        void Opc_ddcb_0a();
        void Opc_ddcb_0b();
        void Opc_ddcb_0c();
        void Opc_ddcb_0d();
        void Opc_ddcb_0e();
        void Opc_ddcb_0f();
        void Opc_ddcb_10();
        void Opc_ddcb_11();
        void Opc_ddcb_12();
        void Opc_ddcb_13();
        void Opc_ddcb_14();
        void Opc_ddcb_15();
        void Opc_ddcb_16();
        void Opc_ddcb_17();
        void Opc_ddcb_18();
        void Opc_ddcb_19();
        void Opc_ddcb_1a();
        void Opc_ddcb_1b();
        void Opc_ddcb_1c();
        void Opc_ddcb_1d();
        void Opc_ddcb_1e();
        void Opc_ddcb_1f();
        void Opc_ddcb_20();
        void Opc_ddcb_21();
        void Opc_ddcb_22();
        void Opc_ddcb_23();
        void Opc_ddcb_24();
        void Opc_ddcb_25();
        void Opc_ddcb_26();
        void Opc_ddcb_27();
        void Opc_ddcb_28();
        void Opc_ddcb_29();
        void Opc_ddcb_2a();
        void Opc_ddcb_2b();
        void Opc_ddcb_2c();
        void Opc_ddcb_2d();
        void Opc_ddcb_2e();
        void Opc_ddcb_2f();
        void Opc_ddcb_30();
        void Opc_ddcb_31();
        void Opc_ddcb_32();
        void Opc_ddcb_33();
        void Opc_ddcb_34();
        void Opc_ddcb_35();
        void Opc_ddcb_36();
        void Opc_ddcb_37();
        void Opc_ddcb_38();
        void Opc_ddcb_39();
        void Opc_ddcb_3a();
        void Opc_ddcb_3b();
        void Opc_ddcb_3c();
        void Opc_ddcb_3d();
        void Opc_ddcb_3e();
        void Opc_ddcb_3f();
        void Opc_ddcb_40();
        void Opc_ddcb_41();
        void Opc_ddcb_42();
        void Opc_ddcb_43();
        void Opc_ddcb_44();
        void Opc_ddcb_45();
        void Opc_ddcb_46();
        void Opc_ddcb_47();
        void Opc_ddcb_48();
        void Opc_ddcb_49();
        void Opc_ddcb_4a();
        void Opc_ddcb_4b();
        void Opc_ddcb_4c();
        void Opc_ddcb_4d();
        void Opc_ddcb_4e();
        void Opc_ddcb_4f();
        void Opc_ddcb_50();
        void Opc_ddcb_51();
        void Opc_ddcb_52();
        void Opc_ddcb_53();
        void Opc_ddcb_54();
        void Opc_ddcb_55();
        void Opc_ddcb_56();
        void Opc_ddcb_57();
        void Opc_ddcb_58();
        void Opc_ddcb_59();
        void Opc_ddcb_5a();
        void Opc_ddcb_5b();
        void Opc_ddcb_5c();
        void Opc_ddcb_5d();
        void Opc_ddcb_5e();
        void Opc_ddcb_5f();
        void Opc_ddcb_60();
        void Opc_ddcb_61();
        void Opc_ddcb_62();
        void Opc_ddcb_63();
        void Opc_ddcb_64();
        void Opc_ddcb_65();
        void Opc_ddcb_66();
        void Opc_ddcb_67();
        void Opc_ddcb_68();
        void Opc_ddcb_69();
        void Opc_ddcb_6a();
        void Opc_ddcb_6b();
        void Opc_ddcb_6c();
        void Opc_ddcb_6d();
        void Opc_ddcb_6e();
        void Opc_ddcb_6f();
        void Opc_ddcb_70();
        void Opc_ddcb_71();
        void Opc_ddcb_72();
        void Opc_ddcb_73();
        void Opc_ddcb_74();
        void Opc_ddcb_75();
        void Opc_ddcb_76();
        void Opc_ddcb_77();
        void Opc_ddcb_78();
        void Opc_ddcb_79();
        void Opc_ddcb_7a();
        void Opc_ddcb_7b();
        void Opc_ddcb_7c();
        void Opc_ddcb_7d();
        void Opc_ddcb_7e();
        void Opc_ddcb_7f();
        void Opc_ddcb_80();
        void Opc_ddcb_81();
        void Opc_ddcb_82();
        void Opc_ddcb_83();
        void Opc_ddcb_84();
        void Opc_ddcb_85();
        void Opc_ddcb_86();
        void Opc_ddcb_87();
        void Opc_ddcb_88();
        void Opc_ddcb_89();
        void Opc_ddcb_8a();
        void Opc_ddcb_8b();
        void Opc_ddcb_8c();
        void Opc_ddcb_8d();
        void Opc_ddcb_8e();
        void Opc_ddcb_8f();
        void Opc_ddcb_90();
        void Opc_ddcb_91();
        void Opc_ddcb_92();
        void Opc_ddcb_93();
        void Opc_ddcb_94();
        void Opc_ddcb_95();
        void Opc_ddcb_96();
        void Opc_ddcb_97();
        void Opc_ddcb_98();
        void Opc_ddcb_99();
        void Opc_ddcb_9a();
        void Opc_ddcb_9b();
        void Opc_ddcb_9c();
        void Opc_ddcb_9d();
        void Opc_ddcb_9e();
        void Opc_ddcb_9f();
        void Opc_ddcb_a0();
        void Opc_ddcb_a1();
        void Opc_ddcb_a2();
        void Opc_ddcb_a3();
        void Opc_ddcb_a4();
        void Opc_ddcb_a5();
        void Opc_ddcb_a6();
        void Opc_ddcb_a7();
        void Opc_ddcb_a8();
        void Opc_ddcb_a9();
        void Opc_ddcb_aa();
        void Opc_ddcb_ab();
        void Opc_ddcb_ac();
        void Opc_ddcb_ad();
        void Opc_ddcb_ae();
        void Opc_ddcb_af();
        void Opc_ddcb_b0();
        void Opc_ddcb_b1();
        void Opc_ddcb_b2();
        void Opc_ddcb_b3();
        void Opc_ddcb_b4();
        void Opc_ddcb_b5();
        void Opc_ddcb_b6();
        void Opc_ddcb_b7();
        void Opc_ddcb_b8();
        void Opc_ddcb_b9();
        void Opc_ddcb_ba();
        void Opc_ddcb_bb();
        void Opc_ddcb_bc();
        void Opc_ddcb_bd();
        void Opc_ddcb_be();
        void Opc_ddcb_bf();
        void Opc_ddcb_c0();
        void Opc_ddcb_c1();
        void Opc_ddcb_c2();
        void Opc_ddcb_c3();
        void Opc_ddcb_c4();
        void Opc_ddcb_c5();
        void Opc_ddcb_c6();
        void Opc_ddcb_c7();
        void Opc_ddcb_c8();
        void Opc_ddcb_c9();
        void Opc_ddcb_ca();
        void Opc_ddcb_cb();
        void Opc_ddcb_cc();
        void Opc_ddcb_cd();
        void Opc_ddcb_ce();
        void Opc_ddcb_cf();
        void Opc_ddcb_d0();
        void Opc_ddcb_d1();
        void Opc_ddcb_d2();
        void Opc_ddcb_d3();
        void Opc_ddcb_d4();
        void Opc_ddcb_d5();
        void Opc_ddcb_d6();
        void Opc_ddcb_d7();
        void Opc_ddcb_d8();
        void Opc_ddcb_d9();
        void Opc_ddcb_da();
        void Opc_ddcb_db();
        void Opc_ddcb_dc();
        void Opc_ddcb_dd();
        void Opc_ddcb_de();
        void Opc_ddcb_df();
        void Opc_ddcb_e0();
        void Opc_ddcb_e1();
        void Opc_ddcb_e2();
        void Opc_ddcb_e3();
        void Opc_ddcb_e4();
        void Opc_ddcb_e5();
        void Opc_ddcb_e6();
        void Opc_ddcb_e7();
        void Opc_ddcb_e8();
        void Opc_ddcb_e9();
        void Opc_ddcb_ea();
        void Opc_ddcb_eb();
        void Opc_ddcb_ec();
        void Opc_ddcb_ed();
        void Opc_ddcb_ee();
        void Opc_ddcb_ef();
        void Opc_ddcb_f0();
        void Opc_ddcb_f1();
        void Opc_ddcb_f2();
        void Opc_ddcb_f3();
        void Opc_ddcb_f4();
        void Opc_ddcb_f5();
        void Opc_ddcb_f6();
        void Opc_ddcb_f7();
        void Opc_ddcb_f8();
        void Opc_ddcb_f9();
        void Opc_ddcb_fa();
        void Opc_ddcb_fb();
        void Opc_ddcb_fc();
        void Opc_ddcb_fd();
        void Opc_ddcb_fe();
        void Opc_ddcb_ff();

        // Opcodes EDxx prototypes.
        void Opc_edxx_40();
        void Opc_edxx_41();
        void Opc_edxx_42();
        void Opc_edxx_43();
        void Opc_edxx_44();
        void Opc_edxx_45();
        void Opc_edxx_46();
        void Opc_edxx_47();
        void Opc_edxx_48();
        void Opc_edxx_49();
        void Opc_edxx_4a();
        void Opc_edxx_4b();
        void Opc_edxx_4c();
        void Opc_edxx_4d();
        void Opc_edxx_4e();
        void Opc_edxx_4f();
        void Opc_edxx_50();
        void Opc_edxx_51();
        void Opc_edxx_52();
        void Opc_edxx_53();
        void Opc_edxx_54();
        void Opc_edxx_55();
        void Opc_edxx_56();
        void Opc_edxx_57();
        void Opc_edxx_58();
        void Opc_edxx_59();
        void Opc_edxx_5a();
        void Opc_edxx_5b();
        void Opc_edxx_5c();
        void Opc_edxx_5d();
        void Opc_edxx_5e();
        void Opc_edxx_5f();
        void Opc_edxx_60();
        void Opc_edxx_61();
        void Opc_edxx_62();
        void Opc_edxx_63();
        void Opc_edxx_64();
        void Opc_edxx_65();
        void Opc_edxx_66();
        void Opc_edxx_67();
        void Opc_edxx_68();
        void Opc_edxx_69();
        void Opc_edxx_6a();
        void Opc_edxx_6b();
        void Opc_edxx_6c();
        void Opc_edxx_6d();
        void Opc_edxx_6e();
        void Opc_edxx_6f();
        void Opc_edxx_70();
        void Opc_edxx_71();
        void Opc_edxx_72();
        void Opc_edxx_73();
        void Opc_edxx_74();
        void Opc_edxx_75();
        void Opc_edxx_76();
        void Opc_edxx_78();
        void Opc_edxx_79();
        void Opc_edxx_7a();
        void Opc_edxx_7b();
        void Opc_edxx_7c();
        void Opc_edxx_7d();
        void Opc_edxx_7e();
        void Opc_edxx_a0();
        void Opc_edxx_a1();
        void Opc_edxx_a2();
        void Opc_edxx_a3();
        void Opc_edxx_a8();
        void Opc_edxx_a9();
        void Opc_edxx_aa();
        void Opc_edxx_ab();
        void Opc_edxx_b0();
        void Opc_edxx_b1();
        void Opc_edxx_b2();
        void Opc_edxx_b3();
        void Opc_edxx_b8();
        void Opc_edxx_b9();
        void Opc_edxx_ba();
        void Opc_edxx_bb();

        // Opcodes FDXX prototypes.
        void Opc_fdxx_09();
        void Opc_fdxx_19();
        void Opc_fdxx_21();
        void Opc_fdxx_22();
        void Opc_fdxx_23();
        void Opc_fdxx_24();
        void Opc_fdxx_25();
        void Opc_fdxx_26();
        void Opc_fdxx_29();
        void Opc_fdxx_2a();
        void Opc_fdxx_2b();
        void Opc_fdxx_2c();
        void Opc_fdxx_2d();
        void Opc_fdxx_2e();
        void Opc_fdxx_34();
        void Opc_fdxx_35();
        void Opc_fdxx_36();
        void Opc_fdxx_39();
        void Opc_fdxx_44();
        void Opc_fdxx_45();
        void Opc_fdxx_46();
        void Opc_fdxx_4c();
        void Opc_fdxx_4d();
        void Opc_fdxx_4e();
        void Opc_fdxx_54();
        void Opc_fdxx_55();
        void Opc_fdxx_56();
        void Opc_fdxx_5c();
        void Opc_fdxx_5d();
        void Opc_fdxx_5e();
        void Opc_fdxx_60();
        void Opc_fdxx_61();
        void Opc_fdxx_62();
        void Opc_fdxx_63();
        void Opc_fdxx_64();
        void Opc_fdxx_65();
        void Opc_fdxx_66();
        void Opc_fdxx_67();
        void Opc_fdxx_68();
        void Opc_fdxx_69();
        void Opc_fdxx_6a();
        void Opc_fdxx_6b();
        void Opc_fdxx_6c();
        void Opc_fdxx_6d();
        void Opc_fdxx_6e();
        void Opc_fdxx_6f();
        void Opc_fdxx_70();
        void Opc_fdxx_71();
        void Opc_fdxx_72();
        void Opc_fdxx_73();
        void Opc_fdxx_74();
        void Opc_fdxx_75();
        void Opc_fdxx_77();
        void Opc_fdxx_7c();
        void Opc_fdxx_7d();
        void Opc_fdxx_7e();
        void Opc_fdxx_84();
        void Opc_fdxx_85();
        void Opc_fdxx_86();
        void Opc_fdxx_8c();
        void Opc_fdxx_8d();
        void Opc_fdxx_8e();
        void Opc_fdxx_94();
        void Opc_fdxx_95();
        void Opc_fdxx_96();
        void Opc_fdxx_9c();
        void Opc_fdxx_9d();
        void Opc_fdxx_9e();
        void Opc_fdxx_a4();
        void Opc_fdxx_a5();
        void Opc_fdxx_a6();
        void Opc_fdxx_ac();
        void Opc_fdxx_ad();
        void Opc_fdxx_ae();
        void Opc_fdxx_b4();
        void Opc_fdxx_b5();
        void Opc_fdxx_b6();
        void Opc_fdxx_bc();
        void Opc_fdxx_bd();
        void Opc_fdxx_be();
        void Opc_fdxx_e1();
        void Opc_fdxx_e3();
        void Opc_fdxx_e5();
        void Opc_fdxx_e9();
        void Opc_fdxx_f9();

        // Opcodes FDCB prototypes.
        void Opc_fdcb_00();
        void Opc_fdcb_01();
        void Opc_fdcb_02();
        void Opc_fdcb_03();
        void Opc_fdcb_04();
        void Opc_fdcb_05();
        void Opc_fdcb_06();
        void Opc_fdcb_07();
        void Opc_fdcb_08();
        void Opc_fdcb_09();
        void Opc_fdcb_0a();
        void Opc_fdcb_0b();
        void Opc_fdcb_0c();
        void Opc_fdcb_0d();
        void Opc_fdcb_0e();
        void Opc_fdcb_0f();
        void Opc_fdcb_10();
        void Opc_fdcb_11();
        void Opc_fdcb_12();
        void Opc_fdcb_13();
        void Opc_fdcb_14();
        void Opc_fdcb_15();
        void Opc_fdcb_16();
        void Opc_fdcb_17();
        void Opc_fdcb_18();
        void Opc_fdcb_19();
        void Opc_fdcb_1a();
        void Opc_fdcb_1b();
        void Opc_fdcb_1c();
        void Opc_fdcb_1d();
        void Opc_fdcb_1e();
        void Opc_fdcb_1f();
        void Opc_fdcb_20();
        void Opc_fdcb_21();
        void Opc_fdcb_22();
        void Opc_fdcb_23();
        void Opc_fdcb_24();
        void Opc_fdcb_25();
        void Opc_fdcb_26();
        void Opc_fdcb_27();
        void Opc_fdcb_28();
        void Opc_fdcb_29();
        void Opc_fdcb_2a();
        void Opc_fdcb_2b();
        void Opc_fdcb_2c();
        void Opc_fdcb_2d();
        void Opc_fdcb_2e();
        void Opc_fdcb_2f();
        void Opc_fdcb_30();
        void Opc_fdcb_31();
        void Opc_fdcb_32();
        void Opc_fdcb_33();
        void Opc_fdcb_34();
        void Opc_fdcb_35();
        void Opc_fdcb_36();
        void Opc_fdcb_37();
        void Opc_fdcb_38();
        void Opc_fdcb_39();
        void Opc_fdcb_3a();
        void Opc_fdcb_3b();
        void Opc_fdcb_3c();
        void Opc_fdcb_3d();
        void Opc_fdcb_3e();
        void Opc_fdcb_3f();
        void Opc_fdcb_40();
        void Opc_fdcb_41();
        void Opc_fdcb_42();
        void Opc_fdcb_43();
        void Opc_fdcb_44();
        void Opc_fdcb_45();
        void Opc_fdcb_46();
        void Opc_fdcb_47();
        void Opc_fdcb_48();
        void Opc_fdcb_49();
        void Opc_fdcb_4a();
        void Opc_fdcb_4b();
        void Opc_fdcb_4c();
        void Opc_fdcb_4d();
        void Opc_fdcb_4e();
        void Opc_fdcb_4f();
        void Opc_fdcb_50();
        void Opc_fdcb_51();
        void Opc_fdcb_52();
        void Opc_fdcb_53();
        void Opc_fdcb_54();
        void Opc_fdcb_55();
        void Opc_fdcb_56();
        void Opc_fdcb_57();
        void Opc_fdcb_58();
        void Opc_fdcb_59();
        void Opc_fdcb_5a();
        void Opc_fdcb_5b();
        void Opc_fdcb_5c();
        void Opc_fdcb_5d();
        void Opc_fdcb_5e();
        void Opc_fdcb_5f();
        void Opc_fdcb_60();
        void Opc_fdcb_61();
        void Opc_fdcb_62();
        void Opc_fdcb_63();
        void Opc_fdcb_64();
        void Opc_fdcb_65();
        void Opc_fdcb_66();
        void Opc_fdcb_67();
        void Opc_fdcb_68();
        void Opc_fdcb_69();
        void Opc_fdcb_6a();
        void Opc_fdcb_6b();
        void Opc_fdcb_6c();
        void Opc_fdcb_6d();
        void Opc_fdcb_6e();
        void Opc_fdcb_6f();
        void Opc_fdcb_70();
        void Opc_fdcb_71();
        void Opc_fdcb_72();
        void Opc_fdcb_73();
        void Opc_fdcb_74();
        void Opc_fdcb_75();
        void Opc_fdcb_76();
        void Opc_fdcb_77();
        void Opc_fdcb_78();
        void Opc_fdcb_79();
        void Opc_fdcb_7a();
        void Opc_fdcb_7b();
        void Opc_fdcb_7c();
        void Opc_fdcb_7d();
        void Opc_fdcb_7e();
        void Opc_fdcb_7f();
        void Opc_fdcb_80();
        void Opc_fdcb_81();
        void Opc_fdcb_82();
        void Opc_fdcb_83();
        void Opc_fdcb_84();
        void Opc_fdcb_85();
        void Opc_fdcb_86();
        void Opc_fdcb_87();
        void Opc_fdcb_88();
        void Opc_fdcb_89();
        void Opc_fdcb_8a();
        void Opc_fdcb_8b();
        void Opc_fdcb_8c();
        void Opc_fdcb_8d();
        void Opc_fdcb_8e();
        void Opc_fdcb_8f();
        void Opc_fdcb_90();
        void Opc_fdcb_91();
        void Opc_fdcb_92();
        void Opc_fdcb_93();
        void Opc_fdcb_94();
        void Opc_fdcb_95();
        void Opc_fdcb_96();
        void Opc_fdcb_97();
        void Opc_fdcb_98();
        void Opc_fdcb_99();
        void Opc_fdcb_9a();
        void Opc_fdcb_9b();
        void Opc_fdcb_9c();
        void Opc_fdcb_9d();
        void Opc_fdcb_9e();
        void Opc_fdcb_9f();
        void Opc_fdcb_a0();
        void Opc_fdcb_a1();
        void Opc_fdcb_a2();
        void Opc_fdcb_a3();
        void Opc_fdcb_a4();
        void Opc_fdcb_a5();
        void Opc_fdcb_a6();
        void Opc_fdcb_a7();
        void Opc_fdcb_a8();
        void Opc_fdcb_a9();
        void Opc_fdcb_aa();
        void Opc_fdcb_ab();
        void Opc_fdcb_ac();
        void Opc_fdcb_ad();
        void Opc_fdcb_ae();
        void Opc_fdcb_af();
        void Opc_fdcb_b0();
        void Opc_fdcb_b1();
        void Opc_fdcb_b2();
        void Opc_fdcb_b3();
        void Opc_fdcb_b4();
        void Opc_fdcb_b5();
        void Opc_fdcb_b6();
        void Opc_fdcb_b7();
        void Opc_fdcb_b8();
        void Opc_fdcb_b9();
        void Opc_fdcb_ba();
        void Opc_fdcb_bb();
        void Opc_fdcb_bc();
        void Opc_fdcb_bd();
        void Opc_fdcb_be();
        void Opc_fdcb_bf();
        void Opc_fdcb_c0();
        void Opc_fdcb_c1();
        void Opc_fdcb_c2();
        void Opc_fdcb_c3();
        void Opc_fdcb_c4();
        void Opc_fdcb_c5();
        void Opc_fdcb_c6();
        void Opc_fdcb_c7();
        void Opc_fdcb_c8();
        void Opc_fdcb_c9();
        void Opc_fdcb_ca();
        void Opc_fdcb_cb();
        void Opc_fdcb_cc();
        void Opc_fdcb_cd();
        void Opc_fdcb_ce();
        void Opc_fdcb_cf();
        void Opc_fdcb_d0();
        void Opc_fdcb_d1();
        void Opc_fdcb_d2();
        void Opc_fdcb_d3();
        void Opc_fdcb_d4();
        void Opc_fdcb_d5();
        void Opc_fdcb_d6();
        void Opc_fdcb_d7();
        void Opc_fdcb_d8();
        void Opc_fdcb_d9();
        void Opc_fdcb_da();
        void Opc_fdcb_db();
        void Opc_fdcb_dc();
        void Opc_fdcb_dd();
        void Opc_fdcb_de();
        void Opc_fdcb_df();
        void Opc_fdcb_e0();
        void Opc_fdcb_e1();
        void Opc_fdcb_e2();
        void Opc_fdcb_e3();
        void Opc_fdcb_e4();
        void Opc_fdcb_e5();
        void Opc_fdcb_e6();
        void Opc_fdcb_e7();
        void Opc_fdcb_e8();
        void Opc_fdcb_e9();
        void Opc_fdcb_ea();
        void Opc_fdcb_eb();
        void Opc_fdcb_ec();
        void Opc_fdcb_ed();
        void Opc_fdcb_ee();
        void Opc_fdcb_ef();
        void Opc_fdcb_f0();
        void Opc_fdcb_f1();
        void Opc_fdcb_f2();
        void Opc_fdcb_f3();
        void Opc_fdcb_f4();
        void Opc_fdcb_f5();
        void Opc_fdcb_f6();
        void Opc_fdcb_f7();
        void Opc_fdcb_f8();
        void Opc_fdcb_f9();
        void Opc_fdcb_fa();
        void Opc_fdcb_fb();
        void Opc_fdcb_fc();
        void Opc_fdcb_fd();
        void Opc_fdcb_fe();
        void Opc_fdcb_ff();

        /* Pre computed variables. */
        static u8 bitval[8];
        static u8 PF_SF_ZF_[256];
        static u8 PF_[256];

        /* Jump tables. */
        typedef void (Z80::* Opc_handler)();
        static Opc_handler Opc_std[256];
        static Opc_handler Opc_cbxx[256];
        static Opc_handler Opc_ddxx[256];
        static Opc_handler Opc_ddcb[256];
        static Opc_handler Opc_edxx[256];
        static Opc_handler Opc_fdxx[256];
        static Opc_handler Opc_fdcb[256];
};


#endif
