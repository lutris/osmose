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
 * File: Opc_ed.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class implements all opcodes with 0xed prefixes.
 * Timing is not 100% Mame compliant (RETN RETI are not certain).
 *
 * Author: Vedder Bruno
 * Date: 10/01/2006, Thailand, Laos Cambodia :-)
 *
 * URL: http://bcz.asterope.fr/
 */

#include "Z80.h"
#include <stdio.h>

/* Opcodes prefixed with 0xED */
void Z80::exec_ed()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    instruction = env.rd8( PC++ );
    (this->*(Opc_edxx[instruction]))();
#ifdef OPCODES_STATS
    ED_Prefix[ instruction ]++;
#endif
}

/* IN B, (C) */
void Z80::Opc_edxx_40()
{
    cycleCount += 12;
    B = env.in( C );
    setFlagAfterInput( B );
}

/* OUT (C), B */
void Z80::Opc_edxx_41()
{
    cycleCount += 12;
    env.out( C, B );
}

/* SBC HL, BC */
void Z80::Opc_edxx_42()
{
    sbcHL(getBC());
}

/* LD (nn), BC */
void Z80::Opc_edxx_43()
{
    cycleCount += 20;
    setNNi16( getBC());
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_44()
{
    cycleCount += 8;
    u8 tmp1 = A;
    A = 0;
    A = sub8( A, tmp1 );
}

/* RETN */
void Z80::Opc_edxx_45()
{
    cycleCount += 14;
    PC = pop();
    IFF1 = IFF2;
    if (IFF2) env.onInterruptsEnabled();
}

/* IM 0 */
void Z80::Opc_edxx_46()
{
    IM=0;
    cycleCount+=8;
}

/* LD I, A */
void Z80::Opc_edxx_47()
{
    I = A;
    cycleCount+=9;
}

/* IN (C), C */
void Z80::Opc_edxx_48()
{
    cycleCount += 12;
    C = env.in( C );
    setFlagAfterInput( C );
}

/* OUT (C), C */
void Z80::Opc_edxx_49()
{
    cycleCount += 12;
    env.out( C, C );
}

/* ADC HL, BC */
void Z80::Opc_edxx_4a()
{
    adcHL(getBC());
}

/* LD BC, (nn) */
void Z80::Opc_edxx_4b()
{
    cycleCount += 20;
    setBC( getNNi16());
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_4c()
{
    Opc_edxx_44();
}

/* RETI */
void Z80::Opc_edxx_4d()
{
    cycleCount += 14;
    PC = pop();
    env.onReturnFromInterrupt();
}

/* IM 0 */
void Z80::Opc_edxx_4e()
{
    IM=0;
    cycleCount+=8;
}

/* LD R, A */
void Z80::Opc_edxx_4f()
{
    R = A;
    Rbit7 = (A & 0x80); // save R bit 7.
    cycleCount+=9;
}

/* IN D, (C) */
void Z80::Opc_edxx_50()
{
    cycleCount += 12;
    D = env.in( C );
    setFlagAfterInput( D );
}

/* OUT (C), D */
void Z80::Opc_edxx_51()
{
    cycleCount += 12;
    env.out( C, D );
}

/* SBC HL, DE */
void Z80::Opc_edxx_52()
{
    sbcHL(getDE());
}

/* LD (nn), DE */
void Z80::Opc_edxx_53()
{
    cycleCount += 20;
    setNNi16( getDE());
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_54()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_55()
{
    Opc_edxx_45();
}

/* IM 1 */
void Z80::Opc_edxx_56()
{
    IM = 1;
    cycleCount+=8;
}

/* LD A, I */
void Z80::Opc_edxx_57()
{
    cycleCount += 9;
    A = I;
    F = (F & (CF | HF | NF)) | PF_SF_ZF_[A];
    F &= ~(HF | PF | NF);
    if (IFF2) F |= PF;    // Copy IFF2 into Parity bit of F.
}

/* IN E, (C) */
void Z80::Opc_edxx_58()
{
    cycleCount += 12;
    E = env.in( C );
    setFlagAfterInput( E );
}

/* OUT (C), E */
void Z80::Opc_edxx_59()
{
    cycleCount += 12;
    env.out( C, E );
}

/* ADC HL, DE */
void Z80::Opc_edxx_5a()
{
    adcHL(getDE());
}

/* LD DE, (nn) */
void Z80::Opc_edxx_5b()
{
    cycleCount += 20;
    setDE( getNNi16());
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_5c()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_5d()
{
    Opc_edxx_45();
}

/* IM 2 */
void Z80::Opc_edxx_5e()
{
    IM=2;
    cycleCount+=8;
}

/* LD A, R */
/* CPU increase R by one on each instruction. But bit7 of R is never */
/* changed by this. It can only by modified with LD R, A instruction.*/
/* That's why this bit is stored separatly in Rbit7 variable.        */
void Z80::Opc_edxx_5f()
{
    cycleCount += 9;
    A = ((R & 0x7F) | Rbit7);
    F = (F & (CF | HF | NF)) | PF_SF_ZF_[A];
    F &= ~(HF | PF | NF);
    if ( IFF2 ) F |= PF; // Copy IFF2 into Parity bit of F.
}

/* IN H, (C) */
void Z80::Opc_edxx_60()
{
    cycleCount += 12;
    H = env.in( C );
    setFlagAfterInput( H );
}

/* OUT (C), H */
void Z80::Opc_edxx_61()
{
    cycleCount += 12;
    env.out( C, H );
}

/* SBC HL, HL */
void Z80::Opc_edxx_62()
{
    sbcHL(getHL());
}

/* LD (nn), HL */
void Z80::Opc_edxx_63()
{
    Opc_std_22();
    cycleCount += 4; // prefixed instruction penality.
}

/* NEG */
void Z80::Opc_edxx_64()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_65()
{
    Opc_edxx_45();
}

/* IM 0 */
void Z80::Opc_edxx_66()
{
    IM=0;
    cycleCount+=8;
}

/* RRD */
void Z80::Opc_edxx_67()
{
    rrd();
}

/* IN L, (C) */
void Z80::Opc_edxx_68()
{
    cycleCount += 12;
    L = env.in( C );
    setFlagAfterInput( L );
}

/* OUT (C), L */
void Z80::Opc_edxx_69()
{
    cycleCount += 12;
    env.out( C, L );
}

/* ADC HL, HL */
void Z80::Opc_edxx_6a()
{
    adcHL(getHL());
}

/* LD HL,(NN) */
void Z80::Opc_edxx_6b()
{
    Opc_std_2a();
    cycleCount += 4; // prefixed instruction penality.
}

/* NEG */
void Z80::Opc_edxx_6c()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_6d()
{
    Opc_edxx_45();
}

/* IM 0 */
void Z80::Opc_edxx_6e()
{
    IM=0;
    cycleCount+=8;
}

/* RLD */
void Z80::Opc_edxx_6f()
{
    rld();
}

/*
0xed70 IN(C) / IN F,(C)
This undocumented instruction read port via C but does not store the result.
Flag register is nevertheless updated
*/
void Z80::Opc_edxx_70()
{
    cycleCount += 12;
    u8 dummy = env.in( C );
    setFlagAfterInput( dummy );
}

/* OUT C, 0 */
void Z80::Opc_edxx_71()
{
    cycleCount += 12;
    env.out( C, 0 );
}

/* SBC HL, SP */
void Z80::Opc_edxx_72()
{
    sbcHL(SP);
}

/* LD (nn), SP */
void Z80::Opc_edxx_73()
{
    cycleCount += 20;
    setNNi16( SP );
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_74()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_75()
{
    Opc_edxx_45();
}

/* IM 1 */
void Z80::Opc_edxx_76()
{
    IM=1;
    cycleCount+=8;
}

/* IN A, (C) */
void Z80::Opc_edxx_78()
{
    cycleCount += 12;
    A = env.in( C );
    setFlagAfterInput( A );
}

/* OUT (C), A */
void Z80::Opc_edxx_79()
{
    cycleCount += 12;
    env.out( C, A );
}

/* ADC HL, SP */
void Z80::Opc_edxx_7a()
{
    adcHL(SP);
}

/* LD SP, (nn) */
void Z80::Opc_edxx_7b()
{
    cycleCount += 20;
    SP = getNNi16();
    PC += 2;
}

/* NEG */
void Z80::Opc_edxx_7c()
{
    Opc_edxx_44();
}

/* RETN */
void Z80::Opc_edxx_7d()
{
    Opc_edxx_45();
}

/* IM 2 */
void Z80::Opc_edxx_7e()
{
    IM=2;
    cycleCount+=8;
}

/* LDI */
void Z80::Opc_edxx_a0()
{
    cycleCount += 16;
    env.wr8( getDE(), env.rd8( getHL()));
    if ( ++L == 0 ) ++H; // HL++
    if ( ++E == 0 ) ++D; // DE++
    if ( C-- == 0 ) --B; // BC--
    F &= ZF | SF | CF;
    if ( getBC() )  F |= PF;
}

/* CPI */
void Z80::Opc_edxx_a1()
{
    u8 tmp_f = F;
    cycleCount += 16;
    cp8( A, env.rd8( getHL()));
    if ( ++L == 0 ) ++H;   // inc HL
    if ( C-- == 0 ) --B;
    F = ( F &~( CF | PF )) | ( tmp_f &CF );
    if ( getBC()) F |= PF; //Clear parity if BC = 0.
}

/* INI */
void Z80::Opc_edxx_a2()
{
    cycleCount += 16;
    env.wr8( getHL(), env.in(C));
    if ( ++L == 0 ) ++H; // HL++
    B = dec8( B );
}

/* OUTI */
void Z80::Opc_edxx_a3()
{
    B = dec8( B );
    env.out( C, env.rd8( getHL()));
    if ( ++L == 0 ) ++H; // HL++
    cycleCount += 16;
}

/* LDD */
void Z80::Opc_edxx_a8()
{
    cycleCount += 16;
    env.wr8( getDE(), env.rd8( getHL())); // (DE) = (HL), HL-- DE-- BC--
    if ( L-- == 0 ) --H;
    if ( E-- == 0 ) --D;
    if ( C-- == 0 ) --B;
    F &= ~( HF | NF | PF );
    if ( getBC()) F |= PF;
}

/* CPD */
void Z80::Opc_edxx_a9()
{
    u8 tmp_f = F;
    cycleCount += 16;
    cp8( A, env.rd8( getHL()));
    if ( L-- == 0 ) --H;
    if ( C-- == 0 ) --B;
    F = ( F &~( CF | PF )) | ( tmp_f &CF );
    if ( getBC()) F |= PF; //Clear parity if BC = 0.
}

/* IND */
void Z80::Opc_edxx_aa()
{
    cycleCount += 16;
    env.wr8( getHL(), env.in(C));
    if ( L-- == 0 ) --H;
    B = dec8( B );
}

/* OUTD */
void Z80::Opc_edxx_ab()
{
    B = dec8( B );
    env.out( C, env.rd8( getHL()));
    if ( L-- == 0 ) --H;
    cycleCount += 16;
}

/* 0xedb0 LDIR
This instruction works as a lot of single instructions.
It's auto repeated by decrementing PC by two. Interrupt can
occurs during execution.
*/
void Z80::Opc_edxx_b0()
{
    Opc_edxx_a0(); // LDI
    if ( F & PF )
    {
        cycleCount += 5;
        PC -= 2;
    }
}

/* 0xedb1 CPIR
This instruction works as a lot of single instructions.
It's auto repeated by decrementing PC by two. Interrupt can
occurs during execution.
*/
void Z80::Opc_edxx_b1()
{
    Opc_edxx_a1();  // CPI
    if (( F &PF ) && !( F &ZF )) // Parity is cleared when BC=0, Zero set when A=(HL)
    {
        cycleCount += 5;
        PC -= 2; // repeat instruction.
    }
}

/* INIR */
void Z80::Opc_edxx_b2()
{
    Opc_edxx_a2(); // INI
    if ( B != 0 )
    {
        cycleCount += 5;
        PC -= 2;
    }
}

/* OTIR */
void Z80::Opc_edxx_b3()
{
    Opc_edxx_a3(); // OTI
    if ( B != 0 )
    {
        cycleCount += 5;
        PC -= 2;
    }

}

/* LDDR */
void Z80::Opc_edxx_b8()
{
    Opc_edxx_a8(); // LDD
    if ( F &PF ) // Parity is cleared when BC == 0
    {
        cycleCount += 5;
        PC -= 2;
    }
}

/* CPDR*/
void Z80::Opc_edxx_b9()
{
    Opc_edxx_a9(); // CPD
    if (( F &PF ) && !( F &ZF ))
    {
        PC -= 2;
        cycleCount += 5;
    }
}

/* INDR */
void Z80::Opc_edxx_ba()
{
    Opc_edxx_aa(); // IND
    if ( B != 0 )
    {
        cycleCount += 5;
        PC -= 2;
    }
}

/* OTDR */
void Z80::Opc_edxx_bb()
{
    Opc_edxx_ab(); // OUTD
    if ( B != 0 )
    {
        cycleCount += 5;
        PC -= 2;
    }
}

Z80::Opc_handler Z80::Opc_edxx[256] =
{
    &Z80::invalid_prefixed_opcode, /* 0xed00 */
    &Z80::invalid_prefixed_opcode, /* 0xed01 */
    &Z80::invalid_prefixed_opcode, /* 0xed02 */
    &Z80::invalid_prefixed_opcode, /* 0xed03 */
    &Z80::invalid_prefixed_opcode, /* 0xed04 */
    &Z80::invalid_prefixed_opcode, /* 0xed05 */
    &Z80::invalid_prefixed_opcode, /* 0xed06 */
    &Z80::invalid_prefixed_opcode, /* 0xed07 */
    &Z80::invalid_prefixed_opcode, /* 0xed08 */
    &Z80::invalid_prefixed_opcode, /* 0xed09 */
    &Z80::invalid_prefixed_opcode, /* 0xed0a */
    &Z80::invalid_prefixed_opcode, /* 0xed0b */
    &Z80::invalid_prefixed_opcode, /* 0xed0c */
    &Z80::invalid_prefixed_opcode, /* 0xed0d */
    &Z80::invalid_prefixed_opcode, /* 0xed0e */
    &Z80::invalid_prefixed_opcode, /* 0xed0f */
    &Z80::invalid_prefixed_opcode, /* 0xed10 */
    &Z80::invalid_prefixed_opcode, /* 0xed11 */
    &Z80::invalid_prefixed_opcode, /* 0xed12 */
    &Z80::invalid_prefixed_opcode, /* 0xed13 */
    &Z80::invalid_prefixed_opcode, /* 0xed14 */
    &Z80::invalid_prefixed_opcode, /* 0xed15 */
    &Z80::invalid_prefixed_opcode, /* 0xed16 */
    &Z80::invalid_prefixed_opcode, /* 0xed17 */
    &Z80::invalid_prefixed_opcode, /* 0xed18 */
    &Z80::invalid_prefixed_opcode, /* 0xed19 */
    &Z80::invalid_prefixed_opcode, /* 0xed1a */
    &Z80::invalid_prefixed_opcode, /* 0xed1b */
    &Z80::invalid_prefixed_opcode, /* 0xed1c */
    &Z80::invalid_prefixed_opcode, /* 0xed1d */
    &Z80::invalid_prefixed_opcode, /* 0xed1e */
    &Z80::invalid_prefixed_opcode, /* 0xed1f */
    &Z80::invalid_prefixed_opcode, /* 0xed20 */
    &Z80::invalid_prefixed_opcode, /* 0xed21 */
    &Z80::invalid_prefixed_opcode, /* 0xed22 */
    &Z80::invalid_prefixed_opcode, /* 0xed23 */
    &Z80::invalid_prefixed_opcode, /* 0xed24 */
    &Z80::invalid_prefixed_opcode, /* 0xed25 */
    &Z80::invalid_prefixed_opcode, /* 0xed26 */
    &Z80::invalid_prefixed_opcode, /* 0xed27 */
    &Z80::invalid_prefixed_opcode, /* 0xed28 */
    &Z80::invalid_prefixed_opcode, /* 0xed29 */
    &Z80::invalid_prefixed_opcode, /* 0xed2a */
    &Z80::invalid_prefixed_opcode, /* 0xed2b */
    &Z80::invalid_prefixed_opcode, /* 0xed2c */
    &Z80::invalid_prefixed_opcode, /* 0xed2d */
    &Z80::invalid_prefixed_opcode, /* 0xed2e */
    &Z80::invalid_prefixed_opcode, /* 0xed2f */
    &Z80::invalid_prefixed_opcode, /* 0xed30 */
    &Z80::invalid_prefixed_opcode, /* 0xed31 */
    &Z80::invalid_prefixed_opcode, /* 0xed32 */
    &Z80::invalid_prefixed_opcode, /* 0xed33 */
    &Z80::invalid_prefixed_opcode, /* 0xed34 */
    &Z80::invalid_prefixed_opcode, /* 0xed35 */
    &Z80::invalid_prefixed_opcode, /* 0xed36 */
    &Z80::invalid_prefixed_opcode, /* 0xed37 */
    &Z80::invalid_prefixed_opcode, /* 0xed38 */
    &Z80::invalid_prefixed_opcode, /* 0xed39 */
    &Z80::invalid_prefixed_opcode, /* 0xed3a */
    &Z80::invalid_prefixed_opcode, /* 0xed3b */
    &Z80::invalid_prefixed_opcode, /* 0xed3c */
    &Z80::invalid_prefixed_opcode, /* 0xed3d */
    &Z80::invalid_prefixed_opcode, /* 0xed3e */
    &Z80::invalid_prefixed_opcode, /* 0xed3f */
    &Z80::Opc_edxx_40,
    &Z80::Opc_edxx_41,
    &Z80::Opc_edxx_42,
    &Z80::Opc_edxx_43,
    &Z80::Opc_edxx_44,
    &Z80::Opc_edxx_45,
    &Z80::Opc_edxx_46,
    &Z80::Opc_edxx_47,
    &Z80::Opc_edxx_48,
    &Z80::Opc_edxx_49,
    &Z80::Opc_edxx_4a,
    &Z80::Opc_edxx_4b,
    &Z80::Opc_edxx_4c,
    &Z80::Opc_edxx_4d,
    &Z80::Opc_edxx_4e,
    &Z80::Opc_edxx_4f,
    &Z80::Opc_edxx_50,
    &Z80::Opc_edxx_51,
    &Z80::Opc_edxx_52,
    &Z80::Opc_edxx_53,
    &Z80::Opc_edxx_54,
    &Z80::Opc_edxx_55,
    &Z80::Opc_edxx_56,
    &Z80::Opc_edxx_57,
    &Z80::Opc_edxx_58,
    &Z80::Opc_edxx_59,
    &Z80::Opc_edxx_5a,
    &Z80::Opc_edxx_5b,
    &Z80::Opc_edxx_5c,
    &Z80::Opc_edxx_5d,
    &Z80::Opc_edxx_5e,
    &Z80::Opc_edxx_5f,
    &Z80::Opc_edxx_60,
    &Z80::Opc_edxx_61,
    &Z80::Opc_edxx_62,
    &Z80::Opc_edxx_63,
    &Z80::Opc_edxx_64,
    &Z80::Opc_edxx_65,
    &Z80::Opc_edxx_66,
    &Z80::Opc_edxx_67,
    &Z80::Opc_edxx_68,
    &Z80::Opc_edxx_69,
    &Z80::Opc_edxx_6a,
    &Z80::Opc_edxx_6b,
    &Z80::Opc_edxx_6c,
    &Z80::Opc_edxx_6d,
    &Z80::Opc_edxx_6e,
    &Z80::Opc_edxx_6f,
    &Z80::Opc_edxx_70,
    &Z80::Opc_edxx_71,
    &Z80::Opc_edxx_72,
    &Z80::Opc_edxx_73,
    &Z80::Opc_edxx_74,
    &Z80::Opc_edxx_75,
    &Z80::Opc_edxx_76,
    &Z80::invalid_prefixed_opcode, /* 0xed77 */
    &Z80::Opc_edxx_78,
    &Z80::Opc_edxx_79,
    &Z80::Opc_edxx_7a,
    &Z80::Opc_edxx_7b,
    &Z80::Opc_edxx_7c,
    &Z80::Opc_edxx_7d,
    &Z80::Opc_edxx_7e,
    &Z80::invalid_prefixed_opcode, /* 0xed7f */
    &Z80::invalid_prefixed_opcode, /* 0xed80 */
    &Z80::invalid_prefixed_opcode, /* 0xed81 */
    &Z80::invalid_prefixed_opcode, /* 0xed82 */
    &Z80::invalid_prefixed_opcode, /* 0xed83 */
    &Z80::invalid_prefixed_opcode, /* 0xed84 */
    &Z80::invalid_prefixed_opcode, /* 0xed85 */
    &Z80::invalid_prefixed_opcode, /* 0xed86 */
    &Z80::invalid_prefixed_opcode, /* 0xed87 */
    &Z80::invalid_prefixed_opcode, /* 0xed88 */
    &Z80::invalid_prefixed_opcode, /* 0xed89 */
    &Z80::invalid_prefixed_opcode, /* 0xed8a */
    &Z80::invalid_prefixed_opcode, /* 0xed8b */
    &Z80::invalid_prefixed_opcode, /* 0xed8c */
    &Z80::invalid_prefixed_opcode, /* 0xed8d */
    &Z80::invalid_prefixed_opcode, /* 0xed8e */
    &Z80::invalid_prefixed_opcode, /* 0xed8f */
    &Z80::invalid_prefixed_opcode, /* 0xed90 */
    &Z80::invalid_prefixed_opcode, /* 0xed91 */
    &Z80::invalid_prefixed_opcode, /* 0xed92 */
    &Z80::invalid_prefixed_opcode, /* 0xed93 */
    &Z80::invalid_prefixed_opcode, /* 0xed94 */
    &Z80::invalid_prefixed_opcode, /* 0xed95 */
    &Z80::invalid_prefixed_opcode, /* 0xed96 */
    &Z80::invalid_prefixed_opcode, /* 0xed97 */
    &Z80::invalid_prefixed_opcode, /* 0xed98 */
    &Z80::invalid_prefixed_opcode, /* 0xed99 */
    &Z80::invalid_prefixed_opcode, /* 0xed9a */
    &Z80::invalid_prefixed_opcode, /* 0xed9b */
    &Z80::invalid_prefixed_opcode, /* 0xed9c */
    &Z80::invalid_prefixed_opcode, /* 0xed9d */
    &Z80::invalid_prefixed_opcode, /* 0xed9e */
    &Z80::invalid_prefixed_opcode, /* 0xed9f */
    &Z80::Opc_edxx_a0,
    &Z80::Opc_edxx_a1,
    &Z80::Opc_edxx_a2,
    &Z80::Opc_edxx_a3,
    &Z80::invalid_prefixed_opcode, /* 0xeda4 */
    &Z80::invalid_prefixed_opcode, /* 0xeda5 */
    &Z80::invalid_prefixed_opcode, /* 0xeda6 */
    &Z80::invalid_prefixed_opcode, /* 0xeda7 */
    &Z80::Opc_edxx_a8,
    &Z80::Opc_edxx_a9,
    &Z80::Opc_edxx_aa,
    &Z80::Opc_edxx_ab,
    &Z80::invalid_prefixed_opcode, /* 0xedac */
    &Z80::invalid_prefixed_opcode, /* 0xedad */
    &Z80::invalid_prefixed_opcode, /* 0xedae */
    &Z80::invalid_prefixed_opcode, /* 0xedaf */
    &Z80::Opc_edxx_b0,
    &Z80::Opc_edxx_b1,
    &Z80::Opc_edxx_b2,
    &Z80::Opc_edxx_b3,
    &Z80::invalid_prefixed_opcode, /* 0xedb4 */
    &Z80::invalid_prefixed_opcode, /* 0xedb5 */
    &Z80::invalid_prefixed_opcode, /* 0xedb6 */
    &Z80::invalid_prefixed_opcode, /* 0xedb7 */
    &Z80::Opc_edxx_b8,
    &Z80::Opc_edxx_b9,
    &Z80::Opc_edxx_ba,
    &Z80::Opc_edxx_bb,
    &Z80::invalid_prefixed_opcode, /* 0xedbc */
    &Z80::invalid_prefixed_opcode, /* 0xedbd */
    &Z80::invalid_prefixed_opcode, /* 0xedbe */
    &Z80::invalid_prefixed_opcode, /* 0xedbf */
    &Z80::invalid_prefixed_opcode, /* 0xedc0 */
    &Z80::invalid_prefixed_opcode, /* 0xedc1 */
    &Z80::invalid_prefixed_opcode, /* 0xedc2 */
    &Z80::invalid_prefixed_opcode, /* 0xedc3 */
    &Z80::invalid_prefixed_opcode, /* 0xedc4 */
    &Z80::invalid_prefixed_opcode, /* 0xedc5 */
    &Z80::invalid_prefixed_opcode, /* 0xedc6 */
    &Z80::invalid_prefixed_opcode, /* 0xedc7 */
    &Z80::invalid_prefixed_opcode, /* 0xedc8 */
    &Z80::invalid_prefixed_opcode, /* 0xedc9 */
    &Z80::invalid_prefixed_opcode, /* 0xedca */
    &Z80::invalid_prefixed_opcode, /* 0xedcb */
    &Z80::invalid_prefixed_opcode, /* 0xedcc */
    &Z80::invalid_prefixed_opcode, /* 0xedcd */
    &Z80::invalid_prefixed_opcode, /* 0xedce */
    &Z80::invalid_prefixed_opcode, /* 0xedcf */
    &Z80::invalid_prefixed_opcode, /* 0xedd0 */
    &Z80::invalid_prefixed_opcode, /* 0xedd1 */
    &Z80::invalid_prefixed_opcode, /* 0xedd2 */
    &Z80::invalid_prefixed_opcode, /* 0xedd3 */
    &Z80::invalid_prefixed_opcode, /* 0xedd4 */
    &Z80::invalid_prefixed_opcode, /* 0xedd5 */
    &Z80::invalid_prefixed_opcode, /* 0xedd6 */
    &Z80::invalid_prefixed_opcode, /* 0xedd7 */
    &Z80::invalid_prefixed_opcode, /* 0xedd8 */
    &Z80::invalid_prefixed_opcode, /* 0xedd9 */
    &Z80::invalid_prefixed_opcode, /* 0xedda */
    &Z80::invalid_prefixed_opcode, /* 0xeddb */
    &Z80::invalid_prefixed_opcode, /* 0xeddc */
    &Z80::invalid_prefixed_opcode, /* 0xeddd */
    &Z80::invalid_prefixed_opcode, /* 0xedde */
    &Z80::invalid_prefixed_opcode, /* 0xeddf */
    &Z80::invalid_prefixed_opcode, /* 0xede0 */
    &Z80::invalid_prefixed_opcode, /* 0xede1 */
    &Z80::invalid_prefixed_opcode, /* 0xede2 */
    &Z80::invalid_prefixed_opcode, /* 0xede3 */
    &Z80::invalid_prefixed_opcode, /* 0xede4 */
    &Z80::invalid_prefixed_opcode, /* 0xede5 */
    &Z80::invalid_prefixed_opcode, /* 0xede6 */
    &Z80::invalid_prefixed_opcode, /* 0xede7 */
    &Z80::invalid_prefixed_opcode, /* 0xede8 */
    &Z80::invalid_prefixed_opcode, /* 0xede9 */
    &Z80::invalid_prefixed_opcode, /* 0xedea */
    &Z80::invalid_prefixed_opcode, /* 0xedeb */
    &Z80::invalid_prefixed_opcode, /* 0xedec */
    &Z80::invalid_prefixed_opcode, /* 0xeded */
    &Z80::invalid_prefixed_opcode, /* 0xedee */
    &Z80::invalid_prefixed_opcode, /* 0xedef */
    &Z80::invalid_prefixed_opcode, /* 0xedf0 */
    &Z80::invalid_prefixed_opcode, /* 0xedf1 */
    &Z80::invalid_prefixed_opcode, /* 0xedf2 */
    &Z80::invalid_prefixed_opcode, /* 0xedf3 */
    &Z80::invalid_prefixed_opcode, /* 0xedf4 */
    &Z80::invalid_prefixed_opcode, /* 0xedf5 */
    &Z80::invalid_prefixed_opcode, /* 0xedf6 */
    &Z80::invalid_prefixed_opcode, /* 0xedf7 */
    &Z80::invalid_prefixed_opcode, /* 0xedf8 */
    &Z80::invalid_prefixed_opcode, /* 0xedf9 */
    &Z80::invalid_prefixed_opcode, /* 0xedfa */
    &Z80::invalid_prefixed_opcode, /* 0xedfb */
    &Z80::invalid_prefixed_opcode, /* 0xedfc */
    &Z80::invalid_prefixed_opcode, /* 0xedfd */
    &Z80::invalid_prefixed_opcode, /* 0xedfe */
    &Z80::invalid_prefixed_opcode  /* 0xedff */
};

