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
 * File: Opc_std.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class implements all opcodes without prefixes.
 * Timing is 100% Mame compliant. Methods here should be used through the jump table
 * "Z80::Opc_std[ opcode ]".
 *
 * Note: This table has no exec() method since cpu uses directly it's jump table.
 *
 * Author: Vedder Bruno
 * Date: 10/01/2006, Thailand, Laos Cambodia :-)
 *
 * URL: http://bcz.asterope.fr
 */

#include "Z80.h"
#include <stdio.h>

/* NOP */
void Z80::Opc_std_00()
{
    cycleCount += 4;
}

/* LD BC,nn */
void Z80::Opc_std_01()
{
    cycleCount += 10;
    C = env.rd8( PC++ );
    B = env.rd8( PC++ );
}

/* LD (BC),A */
void Z80::Opc_std_02()
{
    cycleCount += 7;
    setBCi( A );
}

/*  INC BC */
void Z80::Opc_std_03()
{
    cycleCount += 6;
    setBC( getBC() + 1 );
}

/* INC B */
void Z80::Opc_std_04()
{
    cycleCount += 4;
    B = inc8( B );
}

/* DEC B */
void Z80::Opc_std_05()
{
    cycleCount += 4;
    B = dec8( B );
}

/* LD B,n */
void Z80::Opc_std_06()
{
    cycleCount += 7;
    B = env.rd8( PC++ );
}

/*  RLCA  & FF necessary ?*/
void Z80::Opc_std_07()
{
    cycleCount += 4;
    F = ( F &0xec ) | ( A >> 7 ); /* Outgoing bit is set in carry */
    A = (( A << 1 ) | (( A &0x80 ) >> 7 )) &0xff;
}

/* EX AF, AF1 */
void Z80::Opc_std_08()
{
    //u8 tmp1;
    cycleCount += 4;
    u16 tmp1 = A;
    A = A1;
    A1 = tmp1;
    tmp1 = F;
    F = F1;
    F1 = tmp1;
}

/* ADD HL, BC */
void Z80::Opc_std_09()
{
    cycleCount += 11;
    setHL( add16( getHL(), getBC()));
}

/* LD A,(BC) */
void Z80::Opc_std_0a()
{
    cycleCount += 7;
    A = getBCi();
}

/* DEC BC */
void Z80::Opc_std_0b()
{
    cycleCount += 6;
    if ( C-- == 0 ) --B;
}

/* INC C */
void Z80::Opc_std_0c()
{
    cycleCount += 4;
    C = inc8( C );
}

/* DEC C */
void Z80::Opc_std_0d()
{
    cycleCount += 4;
    C = dec8( C );
}

/* LD C,n */
void Z80::Opc_std_0e()
{
    cycleCount += 7;
    C = env.rd8( PC++ );
}

/*  RRCA & FF necessary ?*/
void Z80::Opc_std_0f()
{
    cycleCount += 4;
    F = ( F &0xec ) | ( A &0x29 ); /* Outgoing bit 0 set to carry */
    A = (( A >> 1 ) | (( A &1 ) << 7 )) &0xff;
}

/* DJNZ */
void Z80::Opc_std_10()
{
    B = ( B - 1 ) &0xff;
    if ( B != 0 )
    {
        cycleCount += 13;
        PC += (s8)env.rd8(PC);
        PC++;
    }
    else
    {
        cycleCount += 8;
        PC++;
    }
}

/* LD DE,nn */
void Z80::Opc_std_11()
{
    cycleCount += 10;
    E = env.rd8( PC++ );
    D = env.rd8( PC++ );
}

/* LD (DE),A */
void Z80::Opc_std_12()
{
    cycleCount += 7;
    setDEi( A );
}

/* INC DE */
void Z80::Opc_std_13()
{
    cycleCount += 6;
    setDE( getDE() + 1 );
}

/* INC D */
void Z80::Opc_std_14()
{
    cycleCount += 4;
    D = inc8( D );
}

/* DEC D */
void Z80::Opc_std_15()
{
    cycleCount += 4;
    D = dec8( D );
}

/* LD D,n */
void Z80::Opc_std_16()
{
    cycleCount += 7;
    D = env.rd8( PC++ );
}

/* RLA */
void Z80::Opc_std_17()
{
    u16 tmp1 = A;
    cycleCount += 4;
    A = ( A << 1 ) &0xff;
    A |= ( F &1 ); /* Get bit 1 from Carry */
    F = ( F &0xEC ) | ( tmp1 >> 7 ); /* Save outgoing bit7 in Carry */
}

/* JR d */
void Z80::Opc_std_18()
{
    // PC += (s8)env.rd8(PC++); Doesn't work anymore with GCC 4.1.1
    // So Split the expression on two differents lines.
    cycleCount += 12;
    PC += (s8)env.rd8(PC);
    PC++;
}

/* ADD HL, DE */
void Z80::Opc_std_19()
{
    cycleCount += 11;
    setHL( add16( getHL(), getDE()));
}

/* LD A,(DE) */
void Z80::Opc_std_1a()
{
    cycleCount += 7;
    A = getDEi();
}

/* DEC DE */
void Z80::Opc_std_1b()
{
    cycleCount += 6;
    setDE( getDE() - 1 );
}

/* INC E */
void Z80::Opc_std_1c()
{
    cycleCount += 4;
    E = inc8( E );
}

/* DEC E */
void Z80::Opc_std_1d()
{
    cycleCount += 4;
    E = dec8( E );
}

/* LD E,n */
void Z80::Opc_std_1e()
{
    cycleCount += 7;
    E = env.rd8( PC++ );
}

/* RRA */
void Z80::Opc_std_1f()
{
    u16 tmp1 = A; /* Save value */
    A = (( A >> 1 ) | (( F &1 ) << 7 )); /* Set carry into Accu. bit7 */
    F = ( F &0xEC ) | ( tmp1 &1 ); /* Carry = outgoing A bit0   */
    cycleCount += 4;
}

/* JR NZ,n */
void Z80::Opc_std_20()
{
    if (!(F & ZF))
    {
        PC += (s8)env.rd8( PC );
        cycleCount += 12; // Mame timing.
    }
    else
    {
        cycleCount += 7;
    }
    PC++;
}

/* LD HL,nn */
void Z80::Opc_std_21()
{
    cycleCount += 10;
    L = env.rd8( PC++ );
    H = env.rd8( PC++ );
}

/* LD (nn),HL */
void Z80::Opc_std_22()
{
    cycleCount += 16;
    setNNi16( getHL());
    PC += 2;
}

/* INC HL */
void Z80::Opc_std_23()
{
    cycleCount += 6;
    if (++L == 0) ++H; // HL++
}

/* INC H */
void Z80::Opc_std_24()
{
    cycleCount += 4;
    H = inc8( H );
}

/* DEC H */
void Z80::Opc_std_25()
{
    cycleCount += 4;
    H = dec8( H );
}

/* LD H,n */
void Z80::Opc_std_26()
{
    cycleCount += 7;
    H = env.rd8( PC++ );
}

/* DAA */
void Z80::Opc_std_27()
{
    u8 t1 = A;
    u8 t2 = 0;
    u8 t3 = ( F &1 );
    u8 t = t3;

    cycleCount += 4;
    if ((( F &0x10 ) != 0 ) || (( t1 &0x0f ) > 0x09 ))
    {
        t2 |= 0x06;
    }
    if (( t3 == 1 ) || ( t1 > 0x9f ) || (( t1 > 0x8f ) && (( t1 &0x0f ) > 0x09 )))
    {
        t2 |= 0x60;
        t = 1;
    }
    if ( t1 > 0x99 )
    {
        t = 1;
    }
    if (( F &0x02 ) != 0 )
    {
        A = sub8( A, t2 );
    }
    else
    {
        A = add8( A, t2 );
    }
    F = ( F &0xfe ) | t;
    F = ( F &0xfb );
    F |= PF_[A];
}

/* JR Z,d */
void Z80::Opc_std_28()
{
    if (( F & ZF ) != 0 )
    {
        cycleCount += 12;
        PC += (s8)env.rd8( PC );
        PC++;
    }
    else
    {
        cycleCount += 7;
        PC++;
    }
}

/* ADD HL,HL */
void Z80::Opc_std_29()
{
    cycleCount += 11;
    setHL( add16( getHL(), getHL()));
}

/* LD HL,nn */
void Z80::Opc_std_2a()
{
    cycleCount += 16;
    setHL( getNNi16());
    PC += 2;
}

/* DEC HL */
void Z80::Opc_std_2b()
{
    cycleCount += 6;
    setHL( getHL() - 1 );
}

/* INC L */
void Z80::Opc_std_2c()
{
    cycleCount += 4;
    L = inc8( L );
}

/* DEC L */
void Z80::Opc_std_2d()
{
    cycleCount += 4;
    L = dec8( L );
}

/* LD L,n */
void Z80::Opc_std_2e()
{
    cycleCount += 7;
    L = env.rd8( PC++ );
}

/* CPL */
void Z80::Opc_std_2f()
{
    cycleCount += 4;
    A ^= 0xff; /* Invert all bits */
    F = (( F &0xc5 ) | 0x12 | ( A &0x28 )); /* Undoc bits set */
}

/* JR NC,d */
void Z80::Opc_std_30()
{
    if (( F &CF ) == 0 )
    {
        cycleCount += 12;
        PC += (s8)env.rd8( PC );
        PC++;
    }
    else
    {
        cycleCount += 7;
        PC++;
    }
}

/* LD SP,nn */
void Z80::Opc_std_31()
{
    cycleCount += 10;
    SP = env.rd16( PC );
    PC += 2;
}

/* LD (nn),a */
void Z80::Opc_std_32()
{
    cycleCount += 13;
    setNNi8( A );
    PC += 2;
}

/* INC SP */
void Z80::Opc_std_33()
{
    cycleCount += 6;
    SP++;
}

/* INC (HL) */
void Z80::Opc_std_34()
{
    cycleCount += 11;
    setHLi( inc8( getHLi()));
}

/* DEC (HL) */
void Z80::Opc_std_35()
{
    cycleCount += 11;
    setHLi( dec8( getHLi()));
}

/* LD (HL),n */
void Z80::Opc_std_36()
{
    cycleCount += 10;
    setHLi( env.rd8( PC++ ));
}

/* SCF */
void Z80::Opc_std_37()
{
    cycleCount += 4;
    F = ( F &0xC4 ) | 1; /* Set Carry */
}

/* JR C,d */
void Z80::Opc_std_38()
{
    if (( F &CF ) != 0 )
    {
        cycleCount += 12;
        PC += (s8)env.rd8( PC );
        PC++;
    }
    else
    {
        cycleCount += 7;
        PC++;
    }
}

/* ADD HL, SP */
void Z80::Opc_std_39()
{
    cycleCount += 11;
    setHL( add16( getHL(), SP ));
}

/* LD A,(nn) */
void Z80::Opc_std_3a()
{
    cycleCount += 13;
    A = getNNi8();
    PC += 2;
}

/* DEC SP */
void Z80::Opc_std_3b()
{
    cycleCount += 6;
    SP--;
}

/* INC A */
void Z80::Opc_std_3c()
{
    cycleCount += 4;
    A = inc8( A );
}

/* DEC A */
void Z80::Opc_std_3d()
{
    cycleCount += 4;
    A = dec8( A );
}

/* LD A,n */
void Z80::Opc_std_3e()
{
    cycleCount += 7;
    A = env.rd8( PC++ );
}

/* CCF */
void Z80::Opc_std_3f()
{
    cycleCount += 4;
    F = (( F &0xc5 ) | (( F &1 ) << 4 ) | ( A &0x28 )) ^ 1;
}

/* LD B, B */
void Z80::Opc_std_40()
{
    nop();
}

/* LD B, C */
void Z80::Opc_std_41()
{
    B = C;
    cycleCount += 4;
}

/* LD B, D */
void Z80::Opc_std_42()
{
    B = D;
    cycleCount += 4;
}

/* LD B, E */
void Z80::Opc_std_43()
{
    B = E;
    cycleCount += 4;
}

/* LD B, H */
void Z80::Opc_std_44()
{
    B = H;
    cycleCount += 4;
}

/* LD B, L */
void Z80::Opc_std_45()
{
    B = L;
    cycleCount += 4;
}

/* LD B, (HL) */
void Z80::Opc_std_46()
{
    B = getHLi();
    cycleCount += 7;
}

/* LD B, A */
void Z80::Opc_std_47()
{
    B = A;
    cycleCount += 4;
}

/* LD C, B */
void Z80::Opc_std_48()
{
    C = B;
    cycleCount += 4;
}

/* LD C, C */
void Z80::Opc_std_49()
{
    nop();
}

/* LD C, D */
void Z80::Opc_std_4a()
{
    C = D;
    cycleCount += 4;
}

/* LD C, E */
void Z80::Opc_std_4b()
{
    C = E;
    cycleCount += 4;
}

/* LD C, H */
void Z80::Opc_std_4c()
{
    C = H;
    cycleCount += 4;
}

/* LD C, L */
void Z80::Opc_std_4d()
{
    C = L;
    cycleCount += 4;
}

/* LD C, (HL) */
void Z80::Opc_std_4e()
{
    C = getHLi();
    cycleCount += 7;
}

/* LD C, A */
void Z80::Opc_std_4f()
{
    C = A;
    cycleCount += 4;
}

/* LD D, B */
void Z80::Opc_std_50()
{
    D = B;
    cycleCount += 4;
}

/* LD D, C */
void Z80::Opc_std_51()
{
    D = C;
    cycleCount += 4;
}

/* LD D, D */
void Z80::Opc_std_52()
{
    nop();
}

/* LD D, E */
void Z80::Opc_std_53()
{
    D = E;
    cycleCount += 4;
}

/* LD D, H */
void Z80::Opc_std_54()
{
    D = H;
    cycleCount += 4;
}

/* LD D, L */
void Z80::Opc_std_55()
{
    D = L;
    cycleCount += 4;
}

/* LD D, (HL) */
void Z80::Opc_std_56()
{
    D = getHLi();
    cycleCount += 7;
}

/* LD D, A */
void Z80::Opc_std_57()
{
    D = A;
    cycleCount += 4;
}

/* LD E, B */
void Z80::Opc_std_58()
{
    E = B;
    cycleCount += 4;
}

/* LD E, C */
void Z80::Opc_std_59()
{
    E = C;
    cycleCount += 4;
}

/* LD E, D */
void Z80::Opc_std_5a()
{
    E = D;
    cycleCount += 4;
}

/* LD E, E */
void Z80::Opc_std_5b()
{
    nop();
}

/* LD E, H */
void Z80::Opc_std_5c()
{
    E = H;
    cycleCount += 4;
}

/* LD E, L */
void Z80::Opc_std_5d()
{
    E = L;
    cycleCount += 4;
}

/* LD E, (HL) */
void Z80::Opc_std_5e()
{
    E = getHLi();
    cycleCount += 7;
}

/* LD E, A */
void Z80::Opc_std_5f()
{
    E = A;
    cycleCount += 4;
}

/* LD H, B */
void Z80::Opc_std_60()
{
    H = B;
    cycleCount += 4;
}

/* LD H, C */
void Z80::Opc_std_61()
{
    H = C;
    cycleCount += 4;
}

/* LD H, D */
void Z80::Opc_std_62()
{
    H = D;
    cycleCount += 4;
}

/* LD H, E */
void Z80::Opc_std_63()
{
    H = E;
    cycleCount += 4;
}

/* LD H, H */
void Z80::Opc_std_64()
{
    nop();
}

/* LD H, L */
void Z80::Opc_std_65()
{
    H = L;
    cycleCount += 4;
}

/* LD H, (HL) */
void Z80::Opc_std_66()
{
    H = getHLi();
    cycleCount += 7;
}

/* LD H, A */
void Z80::Opc_std_67()
{
    H = A;
    cycleCount += 4;
}

/* LD L, B */
void Z80::Opc_std_68()
{
    L = B;
    cycleCount += 4;
}

/* LD L, C */
void Z80::Opc_std_69()
{
    L = C;
    cycleCount += 4;
}

/* LD L, D */
void Z80::Opc_std_6a()
{
    L = D;
    cycleCount += 4;
}

/* LD L, E */
void Z80::Opc_std_6b()
{
    L = E;
    cycleCount += 4;
}

/* LD L, H */
void Z80::Opc_std_6c()
{
    L = H;
    cycleCount += 4;
}

/* LD L, L */
void Z80::Opc_std_6d()
{
    nop();
}

/* LD L, (HL) */
void Z80::Opc_std_6e()
{
    L = getHLi();
    cycleCount += 7;
}

/* LD L, A */
void Z80::Opc_std_6f()
{
    L = A;
    cycleCount += 4;
}

/* LD (HL), B */
void Z80::Opc_std_70()
{
    setHLi(B);
    cycleCount += 7;
}

/* LD (HL), C */
void Z80::Opc_std_71()
{
    setHLi(C);
    cycleCount += 7;
}

/* LD (HL), D */
void Z80::Opc_std_72()
{
    setHLi(D);
    cycleCount += 7;
}

/* LD (HL), E */
void Z80::Opc_std_73()
{
    setHLi(E);
    cycleCount += 7;
}

/* LD (HL), H */
void Z80::Opc_std_74()
{
    setHLi(H);
    cycleCount += 7;
}

/* LD (HL), L */
void Z80::Opc_std_75()
{
    setHLi(L);
    cycleCount += 7;
}

/* HALT */
void Z80::Opc_std_76()
{
    cycleCount += 4;
    cpuHalted = true; /* Put CPU in Halted state */
}

/* LD (HL), A */
void Z80::Opc_std_77()
{
    setHLi(A);
    cycleCount += 7;
}

/* LD A, B */
void Z80::Opc_std_78()
{
    A = B;
    cycleCount += 4;
}

/* LD A, C */
void Z80::Opc_std_79()
{
    A = C;
    cycleCount += 4;
}

/* LD A, D */
void Z80::Opc_std_7a()
{
    A = D;
    cycleCount += 4;
}

/* LD A, E */
void Z80::Opc_std_7b()
{
    A = E;
    cycleCount += 4;
}

/* LD A, H */
void Z80::Opc_std_7c()
{
    A = H;
    cycleCount += 4;
}

/* LD A, L */
void Z80::Opc_std_7d()
{
    A = L;
    cycleCount += 4;
}

/* LD A, (HL) */
void Z80::Opc_std_7e()
{
    A = getHLi();
    cycleCount += 7;
}

/* LD A, A */
void Z80::Opc_std_7f()
{
    nop();
}

/* ADD B */
void Z80::Opc_std_80()
{
    A = add8(A, B);
    cycleCount += 4;
}

/* ADD C */
void Z80::Opc_std_81()
{
    A = add8(A, C);
    cycleCount += 4;
}

/* ADD D */
void Z80::Opc_std_82()
{
    A = add8(A, D);
    cycleCount += 4;
}

/* ADD E */
void Z80::Opc_std_83()
{
    A = add8(A, E);
    cycleCount += 4;
}

/* ADD H */
void Z80::Opc_std_84()
{
    A = add8(A, H);
    cycleCount += 4;
}

/* ADD L */
void Z80::Opc_std_85()
{
    A = add8(A, L);
    cycleCount += 4;
}

/* ADD (HL) */
void Z80::Opc_std_86()
{
    A = add8(A, getHLi());
    cycleCount += 7;
}

/* ADD A */
void Z80::Opc_std_87()
{
    A = add8(A, A);
    cycleCount += 4;
}

/* ADC B */
void Z80::Opc_std_88()
{
    A = adc8(A, B);
    cycleCount += 4;
}

/* ADC C */
void Z80::Opc_std_89()
{
    A = adc8(A, C);
    cycleCount += 4;
}

/* ADC D */
void Z80::Opc_std_8a()
{
    A = adc8(A, D);
    cycleCount += 4;
}

/* ADC E */
void Z80::Opc_std_8b()
{
    A = adc8(A, E);
    cycleCount += 4;
}

/* ADC H */
void Z80::Opc_std_8c()
{
    A = adc8(A, H);
    cycleCount += 4;
}

/* ADC L */
void Z80::Opc_std_8d()
{
    A = adc8(A, L);
    cycleCount += 4;
}

/* ADC (HL) */
void Z80::Opc_std_8e()
{
    A = adc8(A, getHLi());
    cycleCount += 7;
}

/* ADC A */
void Z80::Opc_std_8f()
{
    A = adc8(A, A);
    cycleCount += 4;
}

/* SUB B */
void Z80::Opc_std_90()
{
    A = sub8(A, B);
    cycleCount += 4;
}

/* SUB C */
void Z80::Opc_std_91()
{
    A = sub8(A, C);
    cycleCount += 4;
}

/* SUB D */
void Z80::Opc_std_92()
{
    A = sub8(A, D);
    cycleCount += 4;
}

/* SUB E */
void Z80::Opc_std_93()
{
    A = sub8(A, E);
    cycleCount += 4;
}

/* SUB H */
void Z80::Opc_std_94()
{
    A = sub8(A, H);
    cycleCount += 4;
}

/* SUB L */
void Z80::Opc_std_95()
{
    A = sub8(A, L);
    cycleCount += 4;
}

/* SUB (HL) */
void Z80::Opc_std_96()
{
    A = sub8(A, getHLi());
    cycleCount += 7;
}

/* SUB A */
void Z80::Opc_std_97()
{
    A = sub8(A, A);
    cycleCount += 4;
}

/* SBC B */
void Z80::Opc_std_98()
{
    A = sbc8(A, B);
    cycleCount += 4;
}

/* SBC C */
void Z80::Opc_std_99()
{
    A = sbc8(A, C);
    cycleCount += 4;
}

/* SBC D */
void Z80::Opc_std_9a()
{
    A = sbc8(A, D);
    cycleCount += 4;
}

/* SBC E */
void Z80::Opc_std_9b()
{
    A = sbc8(A, E);
    cycleCount += 4;
}

/* SBC H */
void Z80::Opc_std_9c()
{
    A = sbc8(A, H);
    cycleCount += 4;
}

/* SBC L */
void Z80::Opc_std_9d()
{
    A = sbc8(A, L);
    cycleCount += 4;
}

/* SBC (HL) */
void Z80::Opc_std_9e()
{
    A = sbc8(A, getHLi());
    cycleCount += 7;
}

/* SBC A */
void Z80::Opc_std_9f()
{
    A = sbc8(A, A);
    cycleCount += 4;
}

/* AND B */
void Z80::Opc_std_a0()
{
    A = and8(A, B);
    cycleCount += 4;
}

/* AND C */
void Z80::Opc_std_a1()
{
    A = and8(A, C);
    cycleCount += 4;
}

/* AND D */
void Z80::Opc_std_a2()
{
    A = and8(A, D);
    cycleCount += 4;
}

/* AND E */
void Z80::Opc_std_a3()
{
    A = and8(A, E);
    cycleCount += 4;
}

/* AND H */
void Z80::Opc_std_a4()
{
    A = and8(A, H);
    cycleCount += 4;
}

/* AND L */
void Z80::Opc_std_a5()
{
    A = and8(A, L);
    cycleCount += 4;
}

/* AND (HL) */
void Z80::Opc_std_a6()
{
    A = and8(A, getHLi());
    cycleCount += 7;
}

/* AND A */
void Z80::Opc_std_a7()
{
    A = and8(A, A);
    cycleCount += 4;
}

/* XOR B */
void Z80::Opc_std_a8()
{
    A = xor8(A, B);
    cycleCount += 4;
}

/* XOR C */
void Z80::Opc_std_a9()
{
    A = xor8(A, C);
    cycleCount += 4;
}

/* XOR D */
void Z80::Opc_std_aa()
{
    A = xor8(A, D);
    cycleCount += 4;
}

/* XOR E */
void Z80::Opc_std_ab()
{
    A = xor8(A, E);
    cycleCount += 4;
}

/* XOR H */
void Z80::Opc_std_ac()
{
    A = xor8(A, H);
    cycleCount += 4;
}

/* XOR L */
void Z80::Opc_std_ad()
{
    A = xor8(A, L);
    cycleCount += 4;
}

/* XOR (HL) */
void Z80::Opc_std_ae()
{
    A = xor8(A, getHLi());
    cycleCount += 7;
}

/* XOR A */
void Z80::Opc_std_af()
{
    A = xor8(A, A);
    cycleCount += 4;
}

/* OR B */
void Z80::Opc_std_b0()
{
    A = or8(A, B);
    cycleCount += 4;
}

/* OR C */
void Z80::Opc_std_b1()
{
    A = or8(A, C);
    cycleCount += 4;
}

/* OR D */
void Z80::Opc_std_b2()
{
    A = or8(A, D);
    cycleCount += 4;
}

/* OR E */
void Z80::Opc_std_b3()
{
    A = or8(A, E);
    cycleCount += 4;
}

/* OR H */
void Z80::Opc_std_b4()
{
    A = or8(A, H);
    cycleCount += 4;
}

/* OR L */
void Z80::Opc_std_b5()
{
    A = or8(A, L);
    cycleCount += 4;
}

/* OR (HL) */
void Z80::Opc_std_b6()
{
    A = or8(A, getHLi());
    cycleCount += 7;
}

/* OR A */
void Z80::Opc_std_b7()
{
    A = or8(A, A);
    cycleCount += 4;
}

/* CP B */
void Z80::Opc_std_b8()
{
    cp8(A, B);
    cycleCount += 4;
}

/* CP C */
void Z80::Opc_std_b9()
{
    cp8(A, C);
    cycleCount += 4;
}

/* CP D */
void Z80::Opc_std_ba()
{
    cp8(A, D);
    cycleCount += 4;
}

/* CP E */
void Z80::Opc_std_bb()
{
    cp8(A, E);
    cycleCount += 4;
}

/* CP H */
void Z80::Opc_std_bc()
{
    cp8(A, H);
    cycleCount += 4;
}

/* CP L */
void Z80::Opc_std_bd()
{
    cp8(A, L);
    cycleCount += 4;
}

/* CP (HL) */
void Z80::Opc_std_be()
{
    cp8(A, getHLi());
    cycleCount += 7;
}

/* CP A */
void Z80::Opc_std_bf()
{
    cp8(A, A);
    cycleCount += 4;
}

/* RET NZ */
void Z80::Opc_std_c0()
{
    if (( F &ZF ) == 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* POP BC */
void Z80::Opc_std_c1()
{
    cycleCount += 10;
    setBC( pop());
}

/* JP NZ */
void Z80::Opc_std_c2()
{
    cycleCount += 10;
    if (!(F & ZF))
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* JP nn */
void Z80::Opc_std_c3()
{
    cycleCount += 10;
    PC = env.rd16( PC );
}

/* CALL NZ */
void Z80::Opc_std_c4()
{
    if (( F &ZF ) == 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PUSH BC */
void Z80::Opc_std_c5()
{
    cycleCount += 11;
    push( getBC());
}

/* ADD A,n */
void Z80::Opc_std_c6()
{
    cycleCount += 7;
    A = add8( A, env.rd8( PC++ ));
}

/* RST 0x0 */
void Z80::Opc_std_c7()
{
    rst(0x0);
}

/* RET Z */
void Z80::Opc_std_c8()
{
    if (( F &ZF ) != 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* RET */
void Z80::Opc_std_c9()
{
    cycleCount += 10;
    PC = pop();
}

/* JP Z */
void Z80::Opc_std_ca()
{
    cycleCount += 10;
    if (( F &ZF ) != 0 )
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* PREFIXED INSTRUCTION */
void Z80::Opc_std_cb()
{
    exec_cb();
}

/* CALL Z */
void Z80::Opc_std_cc()
{
    if (( F &ZF ) != 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* CALL */
void Z80::Opc_std_cd()
{
    cycleCount += 17;
    push(PC + 2);
    PC = env.rd16( PC );
}

/* ADC A,n */
void Z80::Opc_std_ce()
{
    cycleCount += 7;
    A = adc8( A, env.rd8( PC++ ));
}

/* RST 0x8 */
void Z80::Opc_std_cf()
{
    rst(0x8);
}

/* RET NC */
void Z80::Opc_std_d0()
{
    if (( F &CF ) == 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* POP DE */
void Z80::Opc_std_d1()
{
    cycleCount += 10;
    setDE(pop());
}

/* JP NC,nn */
void Z80::Opc_std_d2()
{
    cycleCount += 10;
    if (( F &CF ) == 0 )
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* OUT N, A */
void Z80::Opc_std_d3()
{
    cycleCount += 11;
    env.out( env.rd8( PC++ ), A );
}

/* CALL NC */
void Z80::Opc_std_d4()
{
    if (( F & CF ) == 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PUSH DE */
void Z80::Opc_std_d5()
{
    cycleCount += 11;
    push( getDE());
}

/* SUB A,n */
void Z80::Opc_std_d6()
{
    cycleCount += 7;
    A = sub8( A, env.rd8( PC++ ));
}

/* RST 0x10 */
void Z80::Opc_std_d7()
{
    rst(0x10);
}

/* RET C */
void Z80::Opc_std_d8()
{
    if (( F & CF ) != 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* EXX */
void Z80::Opc_std_d9()
{
    u16 tmp1 = B;
    B = B1;
    B1 = tmp1;

    tmp1 = C;
    C = C1;
    C1 = tmp1;

    tmp1 = D;
    D = D1;
    D1 = tmp1;

    tmp1 = E;
    E = E1;
    E1 = tmp1;

    tmp1 = H;
    H = H1;
    H1 = tmp1;

    tmp1 = L;
    L = L1;
    L1 = tmp1;
    cycleCount += 4;
}

/* JP C */
void Z80::Opc_std_da()
{
    cycleCount += 10;
    if (( F &CF ) != 0 )
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* IN A,n */
void Z80::Opc_std_db()
{
    cycleCount += 11;
    A = env.in((u16)( ( A << 8 ) | env.rd8( PC++ )));
}

/* CALL C */
void Z80::Opc_std_dc()
{
    if (( F &CF ) != 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PREFIXED INSTRUCTION */
void Z80::Opc_std_dd()
{
    exec_dd();
}

/* SBC A,n */
void Z80::Opc_std_de()
{
    cycleCount += 7;
    A = sbc8( A, env.rd8( PC++ ));
}

/* RST 0x18 */
void Z80::Opc_std_df()
{
    rst(0x18);
}

/* RET PO */
void Z80::Opc_std_e0()
{
    if (( F & PF ) == 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* POP HL */
void Z80::Opc_std_e1()
{
    cycleCount += 10;
    setHL(pop());
}

/* JP PO */
void Z80::Opc_std_e2()
{
    cycleCount += 10;
    if ((F & PF) == 0 )
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* EX (SP), HL */
void Z80::Opc_std_e3()
{
    cycleCount += 19;
    u16 tmp1 = env.rd16( SP );
    env.wr16( SP, getHL());
    setHL( tmp1 );
}

/* CALL PO */
void Z80::Opc_std_e4()
{
    if (( F &PF ) == 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PUSH HL */
void Z80::Opc_std_e5()
{
    cycleCount += 11;
    push(getHL());
}

/* AND A,n */
void Z80::Opc_std_e6()
{
    cycleCount += 7;
    A = and8( A, env.rd8( PC++ ));
}

/* RST 0x20 */
void Z80::Opc_std_e7()
{
    rst(0x20);
}

/* RET PE */
void Z80::Opc_std_e8()
{
    if (( F &PF ) != 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/*  LD PC, HL or JP HL */
void Z80::Opc_std_e9()
{
    cycleCount += 4; /* SEE MANUAL */
    PC = getHL(); /* JMP HL_value, not (HL) */
}

/* JP PE */
void Z80::Opc_std_ea()
{
    cycleCount += 10;
    if (( F &PF ) != 0 )
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* EX DE, HL */
void Z80::Opc_std_eb()
{
    u16 tmp1 = getDE();
    setDE( getHL());
    setHL( tmp1 );
    cycleCount += 4;
}

/* CALL PE */
void Z80::Opc_std_ec()
{
    if (( F &PF ) != 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PREFIXED INSTRUCTION */
void Z80::Opc_std_ed()
{
    exec_ed();
}

/* XOR A,n */
void Z80::Opc_std_ee()
{
    cycleCount += 7;
    A = xor8( A, env.rd8( PC++ ));
}

/* RST 0x28 */
void Z80::Opc_std_ef()
{
    rst(0x28);
}

/* RET P */
void Z80::Opc_std_f0()
{
    if (( F &SF ) == 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* POP AF */
void Z80::Opc_std_f1()
{
    cycleCount += 10;
    setAF( pop());
}

/* JP P */
void Z80::Opc_std_f2()
{
    cycleCount += 10;
    if (!(F & SF))
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* DI */
void Z80::Opc_std_f3()
{
    cycleCount += 4;
    IFF1 = false;
    IFF2 = false;
#ifdef BUILT_IN_DEBUGGER
    throwDebugEvent(DbgEvtCpuDisableInterrupt, "CPU", "Interrupt Disabled (DI).");
#endif
}

/* CALL P */
void Z80::Opc_std_f4()
{
    if (( F &SF ) == 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PUSH AF */
void Z80::Opc_std_f5()
{
    cycleCount += 11;
    push(getAF());
}

/* OR A,n */
void Z80::Opc_std_f6()
{
    cycleCount += 7;
    A = or8( A, env.rd8( PC++ ));
}

/* RST 0x30 */
void Z80::Opc_std_f7()
{
    rst(0x30);
}

/* RET M */
void Z80::Opc_std_f8()
{
    if (( F &SF ) != 0 )
    {
        cycleCount += 11;
        PC = pop();
    }
    else
    {
        cycleCount += 5;
    }
}

/* LD SP, HL */
void Z80::Opc_std_f9()
{
    cycleCount += 6;
    SP = getHL();
}

/* JP M */
void Z80::Opc_std_fa()
{
    cycleCount += 10;
    if (F & SF)
    {
        PC = env.rd16( PC );
    }
    else
    {
        PC += 2;
    }
}

/* EI */
void Z80::Opc_std_fb()
{
    static bool executing_ei = false;
    cycleCount += 4;
    if ( !executing_ei )
    {
        executing_ei = true;
        // Zilog doc says exec one instruction before clearing flags.
        // This is done to exec retn after EI in interrupt routines.
        step();
        executing_ei = false;
    }
    IFF1 = true; /* CPU accepts interrupts */
    IFF2 = true;
    env.onInterruptsEnabled();
#ifdef BUILT_IN_DEBUGGER
    throwDebugEvent(DbgEvtCpuEnableInterrupt, "CPU", "Interrupt Enabled (EI).");
#endif
}

/* CALL M */
void Z80::Opc_std_fc()
{
    if (( F &SF ) != 0 )
    {
        cycleCount += 17;
        push( PC + 2 );
        PC = env.rd16( PC );
    }
    else
    {
        cycleCount += 10;
        PC += 2;
    }
}

/* PREFIXED INSTRUCTION */
void Z80::Opc_std_fd()
{
    exec_fd();
}

/* CP A,n */
void Z80::Opc_std_fe()
{
    cycleCount += 7;
    sub8( A, env.rd8( PC++ ));
}

/* RST 0x38 */
void Z80::Opc_std_ff()
{
    rst(0x38);
}

Z80::Opc_handler Z80::Opc_std[256] =
{
    &Z80::Opc_std_00,
    &Z80::Opc_std_01,
    &Z80::Opc_std_02,
    &Z80::Opc_std_03,
    &Z80::Opc_std_04,
    &Z80::Opc_std_05,
    &Z80::Opc_std_06,
    &Z80::Opc_std_07,
    &Z80::Opc_std_08,
    &Z80::Opc_std_09,
    &Z80::Opc_std_0a,
    &Z80::Opc_std_0b,
    &Z80::Opc_std_0c,
    &Z80::Opc_std_0d,
    &Z80::Opc_std_0e,
    &Z80::Opc_std_0f,
    &Z80::Opc_std_10,
    &Z80::Opc_std_11,
    &Z80::Opc_std_12,
    &Z80::Opc_std_13,
    &Z80::Opc_std_14,
    &Z80::Opc_std_15,
    &Z80::Opc_std_16,
    &Z80::Opc_std_17,
    &Z80::Opc_std_18,
    &Z80::Opc_std_19,
    &Z80::Opc_std_1a,
    &Z80::Opc_std_1b,
    &Z80::Opc_std_1c,
    &Z80::Opc_std_1d,
    &Z80::Opc_std_1e,
    &Z80::Opc_std_1f,
    &Z80::Opc_std_20,
    &Z80::Opc_std_21,
    &Z80::Opc_std_22,
    &Z80::Opc_std_23,
    &Z80::Opc_std_24,
    &Z80::Opc_std_25,
    &Z80::Opc_std_26,
    &Z80::Opc_std_27,
    &Z80::Opc_std_28,
    &Z80::Opc_std_29,
    &Z80::Opc_std_2a,
    &Z80::Opc_std_2b,
    &Z80::Opc_std_2c,
    &Z80::Opc_std_2d,
    &Z80::Opc_std_2e,
    &Z80::Opc_std_2f,
    &Z80::Opc_std_30,
    &Z80::Opc_std_31,
    &Z80::Opc_std_32,
    &Z80::Opc_std_33,
    &Z80::Opc_std_34,
    &Z80::Opc_std_35,
    &Z80::Opc_std_36,
    &Z80::Opc_std_37,
    &Z80::Opc_std_38,
    &Z80::Opc_std_39,
    &Z80::Opc_std_3a,
    &Z80::Opc_std_3b,
    &Z80::Opc_std_3c,
    &Z80::Opc_std_3d,
    &Z80::Opc_std_3e,
    &Z80::Opc_std_3f,
    &Z80::Opc_std_40,
    &Z80::Opc_std_41,
    &Z80::Opc_std_42,
    &Z80::Opc_std_43,
    &Z80::Opc_std_44,
    &Z80::Opc_std_45,
    &Z80::Opc_std_46,
    &Z80::Opc_std_47,
    &Z80::Opc_std_48,
    &Z80::Opc_std_49,
    &Z80::Opc_std_4a,
    &Z80::Opc_std_4b,
    &Z80::Opc_std_4c,
    &Z80::Opc_std_4d,
    &Z80::Opc_std_4e,
    &Z80::Opc_std_4f,
    &Z80::Opc_std_50,
    &Z80::Opc_std_51,
    &Z80::Opc_std_52,
    &Z80::Opc_std_53,
    &Z80::Opc_std_54,
    &Z80::Opc_std_55,
    &Z80::Opc_std_56,
    &Z80::Opc_std_57,
    &Z80::Opc_std_58,
    &Z80::Opc_std_59,
    &Z80::Opc_std_5a,
    &Z80::Opc_std_5b,
    &Z80::Opc_std_5c,
    &Z80::Opc_std_5d,
    &Z80::Opc_std_5e,
    &Z80::Opc_std_5f,
    &Z80::Opc_std_60,
    &Z80::Opc_std_61,
    &Z80::Opc_std_62,
    &Z80::Opc_std_63,
    &Z80::Opc_std_64,
    &Z80::Opc_std_65,
    &Z80::Opc_std_66,
    &Z80::Opc_std_67,
    &Z80::Opc_std_68,
    &Z80::Opc_std_69,
    &Z80::Opc_std_6a,
    &Z80::Opc_std_6b,
    &Z80::Opc_std_6c,
    &Z80::Opc_std_6d,
    &Z80::Opc_std_6e,
    &Z80::Opc_std_6f,
    &Z80::Opc_std_70,
    &Z80::Opc_std_71,
    &Z80::Opc_std_72,
    &Z80::Opc_std_73,
    &Z80::Opc_std_74,
    &Z80::Opc_std_75,
    &Z80::Opc_std_76,
    &Z80::Opc_std_77,
    &Z80::Opc_std_78,
    &Z80::Opc_std_79,
    &Z80::Opc_std_7a,
    &Z80::Opc_std_7b,
    &Z80::Opc_std_7c,
    &Z80::Opc_std_7d,
    &Z80::Opc_std_7e,
    &Z80::Opc_std_7f,
    &Z80::Opc_std_80,
    &Z80::Opc_std_81,
    &Z80::Opc_std_82,
    &Z80::Opc_std_83,
    &Z80::Opc_std_84,
    &Z80::Opc_std_85,
    &Z80::Opc_std_86,
    &Z80::Opc_std_87,
    &Z80::Opc_std_88,
    &Z80::Opc_std_89,
    &Z80::Opc_std_8a,
    &Z80::Opc_std_8b,
    &Z80::Opc_std_8c,
    &Z80::Opc_std_8d,
    &Z80::Opc_std_8e,
    &Z80::Opc_std_8f,
    &Z80::Opc_std_90,
    &Z80::Opc_std_91,
    &Z80::Opc_std_92,
    &Z80::Opc_std_93,
    &Z80::Opc_std_94,
    &Z80::Opc_std_95,
    &Z80::Opc_std_96,
    &Z80::Opc_std_97,
    &Z80::Opc_std_98,
    &Z80::Opc_std_99,
    &Z80::Opc_std_9a,
    &Z80::Opc_std_9b,
    &Z80::Opc_std_9c,
    &Z80::Opc_std_9d,
    &Z80::Opc_std_9e,
    &Z80::Opc_std_9f,
    &Z80::Opc_std_a0,
    &Z80::Opc_std_a1,
    &Z80::Opc_std_a2,
    &Z80::Opc_std_a3,
    &Z80::Opc_std_a4,
    &Z80::Opc_std_a5,
    &Z80::Opc_std_a6,
    &Z80::Opc_std_a7,
    &Z80::Opc_std_a8,
    &Z80::Opc_std_a9,
    &Z80::Opc_std_aa,
    &Z80::Opc_std_ab,
    &Z80::Opc_std_ac,
    &Z80::Opc_std_ad,
    &Z80::Opc_std_ae,
    &Z80::Opc_std_af,
    &Z80::Opc_std_b0,
    &Z80::Opc_std_b1,
    &Z80::Opc_std_b2,
    &Z80::Opc_std_b3,
    &Z80::Opc_std_b4,
    &Z80::Opc_std_b5,
    &Z80::Opc_std_b6,
    &Z80::Opc_std_b7,
    &Z80::Opc_std_b8,
    &Z80::Opc_std_b9,
    &Z80::Opc_std_ba,
    &Z80::Opc_std_bb,
    &Z80::Opc_std_bc,
    &Z80::Opc_std_bd,
    &Z80::Opc_std_be,
    &Z80::Opc_std_bf,
    &Z80::Opc_std_c0,
    &Z80::Opc_std_c1,
    &Z80::Opc_std_c2,
    &Z80::Opc_std_c3,
    &Z80::Opc_std_c4,
    &Z80::Opc_std_c5,
    &Z80::Opc_std_c6,
    &Z80::Opc_std_c7,
    &Z80::Opc_std_c8,
    &Z80::Opc_std_c9,
    &Z80::Opc_std_ca,
    &Z80::Opc_std_cb,
    &Z80::Opc_std_cc,
    &Z80::Opc_std_cd,
    &Z80::Opc_std_ce,
    &Z80::Opc_std_cf,
    &Z80::Opc_std_d0,
    &Z80::Opc_std_d1,
    &Z80::Opc_std_d2,
    &Z80::Opc_std_d3,
    &Z80::Opc_std_d4,
    &Z80::Opc_std_d5,
    &Z80::Opc_std_d6,
    &Z80::Opc_std_d7,
    &Z80::Opc_std_d8,
    &Z80::Opc_std_d9,
    &Z80::Opc_std_da,
    &Z80::Opc_std_db,
    &Z80::Opc_std_dc,
    &Z80::Opc_std_dd,
    &Z80::Opc_std_de,
    &Z80::Opc_std_df,
    &Z80::Opc_std_e0,
    &Z80::Opc_std_e1,
    &Z80::Opc_std_e2,
    &Z80::Opc_std_e3,
    &Z80::Opc_std_e4,
    &Z80::Opc_std_e5,
    &Z80::Opc_std_e6,
    &Z80::Opc_std_e7,
    &Z80::Opc_std_e8,
    &Z80::Opc_std_e9,
    &Z80::Opc_std_ea,
    &Z80::Opc_std_eb,
    &Z80::Opc_std_ec,
    &Z80::Opc_std_ed,
    &Z80::Opc_std_ee,
    &Z80::Opc_std_ef,
    &Z80::Opc_std_f0,
    &Z80::Opc_std_f1,
    &Z80::Opc_std_f2,
    &Z80::Opc_std_f3,
    &Z80::Opc_std_f4,
    &Z80::Opc_std_f5,
    &Z80::Opc_std_f6,
    &Z80::Opc_std_f7,
    &Z80::Opc_std_f8,
    &Z80::Opc_std_f9,
    &Z80::Opc_std_fa,
    &Z80::Opc_std_fb,
    &Z80::Opc_std_fc,
    &Z80::Opc_std_fd,
    &Z80::Opc_std_fe,
    &Z80::Opc_std_ff
};
