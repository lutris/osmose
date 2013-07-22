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
 * File: Opc_fd.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class implements all opcodes with 0xfd prefixes.
 * Timing is 100% Mame compliant.
 *
 * Note: 99% of this code has been generated.
 *
 * Author: Vedder Bruno
 * Date: 10/01/2006, Thailand, Laos Cambodia :-)
 *
 * URL: http://bcz.asterope.fr
 */

#include "Z80.h"

/* Opcodes prefixed with 0xFD */
void Z80::exec_fd()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    instruction = env.rd8( PC++ );
    (this->*(Opc_fdxx[instruction]))();
#ifdef OPCODES_STATS
    FD_Prefix[ instruction ]++;
#endif
}

/* ADD IY, BC */
void Z80::Opc_fdxx_09()
{
    IY = add16(IY, getBC());
    cycleCount += 15;
}

/* ADD IY, DE */
void Z80::Opc_fdxx_19()
{
    IY = add16(IY, getDE());
    cycleCount += 15;
}

/* LD IY, (nn) */
void Z80::Opc_fdxx_21()
{
    IY = env.rd16(PC);
    PC+=2;
    cycleCount += 14;
}

/* LD (NN),IY */
void Z80::Opc_fdxx_22()
{
    setNNi16(IY);
    PC+=2;
    cycleCount += 20;
}

/* INC IY */
void Z80::Opc_fdxx_23()
{
    IY++;
    cycleCount += 10;
}

/* INC IYH */
void Z80::Opc_fdxx_24()
{
    IY = (IY & 0xFF) | (inc8(IY >> 8) << 8);
    cycleCount += 9;
}

/* DEC IYH */
void Z80::Opc_fdxx_25()
{
    IY = (IY & 0xFF) | (dec8(IY >> 8) << 8);
    cycleCount += 9;
}

/* LD IYH, n */
void Z80::Opc_fdxx_26()
{
    IY = ((IY & 0xFF) |  env.rd8(PC++) << 8);
    cycleCount += 9;
}

/* ADD IY, IY */
void Z80::Opc_fdxx_29()
{
    IY = add16(IY, IY);
    cycleCount += 15;
}

/* LD IY,(nn) */
void Z80::Opc_fdxx_2a()
{
    IY = getNNi16();
    PC += 2;
    cycleCount += 20;
}

/* DEC IY */
void Z80::Opc_fdxx_2b()
{
    IY--;
    cycleCount += 10;
}

/* INC IYL */
void Z80::Opc_fdxx_2c()
{
    IY = (IY & 0xFF00) | (inc8(IY & 0xFF));
    cycleCount += 9;
}

/* DEC IYL */
void Z80::Opc_fdxx_2d()
{
    IY = (IY & 0xFF00) | (dec8(IY & 0xFF));
    cycleCount += 9;
}

/* LD IYL, n */
void Z80::Opc_fdxx_2e()
{
    IY = (IY & 0xFF00) | env.rd8(PC++);
    cycleCount += 9;
}

/* INC (IY+d) */
void Z80::Opc_fdxx_34()
{
    setIYdi(inc8(getIYdi()));
    PC++;
    cycleCount += 23;
}

/* DEC (IY+d) */
void Z80::Opc_fdxx_35()
{
    setIYdi(dec8(getIYdi()));
    PC++;
    cycleCount += 23;
}

/* LD (IY+d), n */
void Z80::Opc_fdxx_36()
{
    setIYdi(env.rd8(PC+1));
    PC += 2;
    cycleCount += 19;
}

/* ADD IY, SP */
void Z80::Opc_fdxx_39()
{
    IY = add16(IY, SP);
    cycleCount += 15;
}

/* LD B, IYH */
void Z80::Opc_fdxx_44()
{
    B = (IY >> 8);
    cycleCount += 9;
}

/* LD B, IYL */
void Z80::Opc_fdxx_45()
{
    B = (IY & 0xFF);
    cycleCount += 9;
}

/* LD B, (IY+d) */
void Z80::Opc_fdxx_46()
{
    B = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD C, IYH */
void Z80::Opc_fdxx_4c()
{
    C = (IY >> 8);
    cycleCount += 9;
}

/* LD C, IYL */
void Z80::Opc_fdxx_4d()
{
    C = (IY & 0xFF);
    cycleCount += 9;
}

/* LD C, (IY+d) */
void Z80::Opc_fdxx_4e()
{
    C = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD D, IYH */
void Z80::Opc_fdxx_54()
{
    D = (IY >> 8);
    cycleCount += 9;
}

/* LD D, IYL */
void Z80::Opc_fdxx_55()
{
    D = (IY & 0xFF);
    cycleCount += 9;
}

/* LD D, (IY+d) */
void Z80::Opc_fdxx_56()
{
    D = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD E, IYH */
void Z80::Opc_fdxx_5c()
{
    E = (IY >> 8);
    cycleCount += 9;
}

/* LD E, IYL */
void Z80::Opc_fdxx_5d()
{
    E = (IY & 0xFF);
    cycleCount += 9;
}

/* LD E, (IY+d) */
void Z80::Opc_fdxx_5e()
{
    E = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD IYH, B */
void Z80::Opc_fdxx_60()
{
    IY = ( IY & 0xFF ) | (( u16 )B << 8 );
    cycleCount += 9;
}

/* LD IYH, C */
void Z80::Opc_fdxx_61()
{
    IY = ( IY & 0xFF ) | (( u16 )C << 8 );
    cycleCount += 9;
}

/* LD IYH, D */
void Z80::Opc_fdxx_62()
{
    IY = ( IY & 0xFF ) | (( u16 )D << 8 );
    cycleCount += 9;
}

/* LD IYH, E */
void Z80::Opc_fdxx_63()
{
    IY = ( IY & 0xFF ) | (( u16 )E << 8 );
    cycleCount += 9;
}

/* LD IYH, IYH */
void Z80::Opc_fdxx_64()
{
    IY = IY; // Do nothing;
    cycleCount += 9;
}

/* LD IYH, IYL */
void Z80::Opc_fdxx_65()
{
    IY = ( IY & 0xFF ) | (( IY & 0xFF ) << 8 );
    cycleCount += 9;
}

/* LD H, (IY+d) */
void Z80::Opc_fdxx_66()
{
    H = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD IYH, A */
void Z80::Opc_fdxx_67()
{
    IY = ( IY & 0xFF ) | (( u16 )A << 8 );
    cycleCount += 9;
}

/* LD IYL, B */
void Z80::Opc_fdxx_68()
{
    IY = ( IY & 0xFF00 ) | B;
    cycleCount += 9;
}

/* LD IYL, C */
void Z80::Opc_fdxx_69()
{
    IY = ( IY & 0xFF00 ) | C;
    cycleCount += 9;
}

/* LD IYL, D */
void Z80::Opc_fdxx_6a()
{
    IY = ( IY & 0xFF00 ) | D;
    cycleCount += 9;
}

/* LD IYL, E */
void Z80::Opc_fdxx_6b()
{
    IY = ( IY & 0xFF00 ) | E;
    cycleCount += 9;
}

/* LD IYL, IYH */
void Z80::Opc_fdxx_6c()
{
    IY = ( IY & 0xFF00 ) | ( IY >> 8 );
    cycleCount += 9;
}

/* LD IYL, IYL */
void Z80::Opc_fdxx_6d()
{
    IY = IY; // Do nothing;
    cycleCount += 9;
}

/* LD L, (IY+d) */
void Z80::Opc_fdxx_6e()
{
    L = getIYdi();
    PC++;
    cycleCount += 19;
}

/* LD IYL, A */
void Z80::Opc_fdxx_6f()
{
    IY = ( IY & 0xFF00 ) | A;
    cycleCount += 9;
}

/* LD (IY+d), B */
void Z80::Opc_fdxx_70()
{
    setIYdi(B);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), C */
void Z80::Opc_fdxx_71()
{
    setIYdi(C);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), D */
void Z80::Opc_fdxx_72()
{
    setIYdi(D);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), E */
void Z80::Opc_fdxx_73()
{
    setIYdi(E);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), H */
void Z80::Opc_fdxx_74()
{
    setIYdi(H);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), L */
void Z80::Opc_fdxx_75()
{
    setIYdi(L);
    PC++;
    cycleCount += 19;
}

/* LD (IY+d), A */
void Z80::Opc_fdxx_77()
{
    setIYdi(A);
    PC++;
    cycleCount += 19;
}

/* LD A, IYH */
void Z80::Opc_fdxx_7c()
{
    A = (IY >> 8);
    cycleCount += 9;
}

/* LD A, IYL */
void Z80::Opc_fdxx_7d()
{
    A = (IY & 0xFF);
    cycleCount += 9;
}

/* LD A, (IY+d) */
void Z80::Opc_fdxx_7e()
{
    A = getIYdi();
    PC++;
    cycleCount += 19;
}

/* ADD A, IYH */
void Z80::Opc_fdxx_84()
{
    A = add8(A, IY >> 8);
    cycleCount += 9;
}

/* ADD A, IYL */
void Z80::Opc_fdxx_85()
{
    A = add8(A, IY & 0xFF);
    cycleCount += 9;
}

/* ADD A, (IY+d) */
void Z80::Opc_fdxx_86()
{
    A = add8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* ADC A, IYH */
void Z80::Opc_fdxx_8c()
{
    A = adc8(A, IY >> 8);
    cycleCount += 9;
}

/* ADC A, IYL */
void Z80::Opc_fdxx_8d()
{
    A = adc8(A, IY & 0xFF);
    cycleCount += 9;
}

/* ADC A, (IY+d) */
void Z80::Opc_fdxx_8e()
{
    A = adc8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* SUB A, IYH */
void Z80::Opc_fdxx_94()
{
    A = sub8(A, IY >> 8);
    cycleCount += 9;
}

/* SUB A, IYL */
void Z80::Opc_fdxx_95()
{
    A = sub8(A, IY & 0xFF);
    cycleCount += 9;
}

/* SUB A, (IY+d) */
void Z80::Opc_fdxx_96()
{
    A = sub8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* SBC A, IYH */
void Z80::Opc_fdxx_9c()
{
    A = sbc8(A, IY >> 8);
    cycleCount += 9;
}

/* SBC A, IYL */
void Z80::Opc_fdxx_9d()
{
    A = sbc8(A, IY & 0xFF);
    cycleCount += 9;
}

/* SBC A, (IY+d) */
void Z80::Opc_fdxx_9e()
{
    A = sbc8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* AND A, IYH */
void Z80::Opc_fdxx_a4()
{
    A = and8(A, IY >> 8);
    cycleCount += 9;
}

/* AND A, IYL */
void Z80::Opc_fdxx_a5()
{
    A = and8(A, IY & 0xFF);
    cycleCount += 9;
}

/* AND A, (IY+d) */
void Z80::Opc_fdxx_a6()
{
    A = and8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* XOR A, IYH */
void Z80::Opc_fdxx_ac()
{
    A = xor8(A, IY >> 8);
    cycleCount += 9;
}

/* XOR A, IYL */
void Z80::Opc_fdxx_ad()
{
    A = xor8(A, IY & 0xFF);
    cycleCount += 9;
}

/* XOR A, (IY+d) */
void Z80::Opc_fdxx_ae()
{
    A = xor8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* OR A, IYH */
void Z80::Opc_fdxx_b4()
{
    A = or8(A, IY >> 8);
    cycleCount += 9;
}

/* OR A, IYL */
void Z80::Opc_fdxx_b5()
{
    A = or8(A, IY & 0xFF);
    cycleCount += 9;
}

/* OR A, (IY+d) */
void Z80::Opc_fdxx_b6()
{
    A = or8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* CP A, IYH */
void Z80::Opc_fdxx_bc()
{
    cp8(A, IY >> 8);
    cycleCount += 9;
}

/* CP A, IYL */
void Z80::Opc_fdxx_bd()
{
    cp8(A, IY & 0xFF);
    cycleCount += 9;
}

/* CP A, (IY+d) */
void Z80::Opc_fdxx_be()
{
    cp8(A, getIYdi());
    PC++;
    cycleCount += 19;
}

/* POP IY */
void Z80::Opc_fdxx_e1()
{
    IY = pop();
    cycleCount += 14;
}

/* EX (SP), IY */
void Z80::Opc_fdxx_e3()
{
    u16 tmp1 = env.rd16( SP );
    env.wr16( SP, IY );
    IY = tmp1;
    cycleCount += 23;
}

/* PUSH IY */
void Z80::Opc_fdxx_e5()
{
    push(IY);
    cycleCount += 15;
}

/* JP IY or LD PC, IY */
void Z80::Opc_fdxx_e9()
{
    PC = IY;
    cycleCount += 8;
}

/* LD SP, IY */
void Z80::Opc_fdxx_f9()
{
    SP = IY;
    cycleCount += 10;
}

Z80::Opc_handler Z80::Opc_fdxx[256] =
{
    &Z80::invalid_opcode,	/* 0xfd00 */
    &Z80::invalid_opcode,	/* 0xfd01 */
    &Z80::invalid_opcode,	/* 0xfd02 */
    &Z80::invalid_opcode,	/* 0xfd03 */
    &Z80::invalid_opcode,	/* 0xfd04 */
    &Z80::invalid_opcode,	/* 0xfd05 */
    &Z80::invalid_opcode,	/* 0xfd06 */
    &Z80::invalid_opcode,	/* 0xfd07 */
    &Z80::invalid_opcode,	/* 0xfd08 */
    &Z80::Opc_fdxx_09,
    &Z80::invalid_opcode,	/* 0xfd0a */
    &Z80::invalid_opcode,	/* 0xfd0b */
    &Z80::invalid_opcode,	/* 0xfd0c */
    &Z80::invalid_opcode,	/* 0xfd0d */
    &Z80::invalid_opcode,	/* 0xfd0e */
    &Z80::invalid_opcode,	/* 0xfd0f */
    &Z80::invalid_opcode,	/* 0xfd10 */
    &Z80::invalid_opcode,	/* 0xfd11 */
    &Z80::invalid_opcode,	/* 0xfd12 */
    &Z80::invalid_opcode,	/* 0xfd13 */
    &Z80::invalid_opcode,	/* 0xfd14 */
    &Z80::invalid_opcode,	/* 0xfd15 */
    &Z80::invalid_opcode,	/* 0xfd16 */
    &Z80::invalid_opcode,	/* 0xfd17 */
    &Z80::invalid_opcode,	/* 0xfd18 */
    &Z80::Opc_fdxx_19,
    &Z80::invalid_opcode,	/* 0xfd1a */
    &Z80::invalid_opcode,	/* 0xfd1b */
    &Z80::invalid_opcode,	/* 0xfd1c */
    &Z80::invalid_opcode,	/* 0xfd1d */
    &Z80::invalid_opcode,	/* 0xfd1e */
    &Z80::invalid_opcode,	/* 0xfd1f */
    &Z80::invalid_opcode,	/* 0xfd20 */
    &Z80::Opc_fdxx_21,
    &Z80::Opc_fdxx_22,
    &Z80::Opc_fdxx_23,
    &Z80::Opc_fdxx_24,
    &Z80::Opc_fdxx_25,
    &Z80::Opc_fdxx_26,
    &Z80::invalid_opcode,	/* 0xfd27 */
    &Z80::invalid_opcode,	/* 0xfd28 */
    &Z80::Opc_fdxx_29,
    &Z80::Opc_fdxx_2a,
    &Z80::Opc_fdxx_2b,
    &Z80::Opc_fdxx_2c,
    &Z80::Opc_fdxx_2d,
    &Z80::Opc_fdxx_2e,
    &Z80::invalid_opcode,	/* 0xfd2f */
    &Z80::invalid_opcode,	/* 0xfd30 */
    &Z80::invalid_opcode,	/* 0xfd31 */
    &Z80::invalid_opcode,	/* 0xfd32 */
    &Z80::invalid_opcode,	/* 0xfd33 */
    &Z80::Opc_fdxx_34,
    &Z80::Opc_fdxx_35,
    &Z80::Opc_fdxx_36,
    &Z80::invalid_opcode,	/* 0xfd37 */
    &Z80::invalid_opcode,	/* 0xfd38 */
    &Z80::Opc_fdxx_39,
    &Z80::invalid_opcode,	/* 0xfd3a */
    &Z80::invalid_opcode,	/* 0xfd3b */
    &Z80::invalid_opcode,	/* 0xfd3c */
    &Z80::invalid_opcode,	/* 0xfd3d */
    &Z80::invalid_opcode,	/* 0xfd3e */
    &Z80::invalid_opcode,	/* 0xfd3f */
    &Z80::invalid_opcode,	/* 0xfd40 */
    &Z80::invalid_opcode,	/* 0xfd41 */
    &Z80::invalid_opcode,	/* 0xfd42 */
    &Z80::invalid_opcode,	/* 0xfd43 */
    &Z80::Opc_fdxx_44,
    &Z80::Opc_fdxx_45,
    &Z80::Opc_fdxx_46,
    &Z80::invalid_opcode,	/* 0xfd47 */
    &Z80::invalid_opcode,	/* 0xfd48 */
    &Z80::invalid_opcode,	/* 0xfd49 */
    &Z80::invalid_opcode,	/* 0xfd4a */
    &Z80::invalid_opcode,	/* 0xfd4b */
    &Z80::Opc_fdxx_4c,
    &Z80::Opc_fdxx_4d,
    &Z80::Opc_fdxx_4e,
    &Z80::invalid_opcode,	/* 0xfd4f */
    &Z80::invalid_opcode,	/* 0xfd50 */
    &Z80::invalid_opcode,	/* 0xfd51 */
    &Z80::invalid_opcode,	/* 0xfd52 */
    &Z80::invalid_opcode,	/* 0xfd53 */
    &Z80::Opc_fdxx_54,
    &Z80::Opc_fdxx_55,
    &Z80::Opc_fdxx_56,
    &Z80::invalid_opcode,	/* 0xfd57 */
    &Z80::invalid_opcode,	/* 0xfd58 */
    &Z80::invalid_opcode,	/* 0xfd59 */
    &Z80::invalid_opcode,	/* 0xfd5a */
    &Z80::invalid_opcode,	/* 0xfd5b */
    &Z80::Opc_fdxx_5c,
    &Z80::Opc_fdxx_5d,
    &Z80::Opc_fdxx_5e,
    &Z80::invalid_opcode,	/* 0xfd5f */
    &Z80::Opc_fdxx_60,
    &Z80::Opc_fdxx_61,
    &Z80::Opc_fdxx_62,
    &Z80::Opc_fdxx_63,
    &Z80::Opc_fdxx_64,
    &Z80::Opc_fdxx_65,
    &Z80::Opc_fdxx_66,
    &Z80::Opc_fdxx_67,
    &Z80::Opc_fdxx_68,
    &Z80::Opc_fdxx_69,
    &Z80::Opc_fdxx_6a,
    &Z80::Opc_fdxx_6b,
    &Z80::Opc_fdxx_6c,
    &Z80::Opc_fdxx_6d,
    &Z80::Opc_fdxx_6e,
    &Z80::Opc_fdxx_6f,
    &Z80::Opc_fdxx_70,
    &Z80::Opc_fdxx_71,
    &Z80::Opc_fdxx_72,
    &Z80::Opc_fdxx_73,
    &Z80::Opc_fdxx_74,
    &Z80::Opc_fdxx_75,
    &Z80::invalid_opcode,	/* 0xfd76 */
    &Z80::Opc_fdxx_77,
    &Z80::invalid_opcode,	/* 0xfd78 */
    &Z80::invalid_opcode,	/* 0xfd79 */
    &Z80::invalid_opcode,	/* 0xfd7a */
    &Z80::invalid_opcode,	/* 0xfd7b */
    &Z80::Opc_fdxx_7c,
    &Z80::Opc_fdxx_7d,
    &Z80::Opc_fdxx_7e,
    &Z80::invalid_opcode,	/* 0xfd7f */
    &Z80::invalid_opcode,	/* 0xfd80 */
    &Z80::invalid_opcode,	/* 0xfd81 */
    &Z80::invalid_opcode,	/* 0xfd82 */
    &Z80::invalid_opcode,	/* 0xfd83 */
    &Z80::Opc_fdxx_84,
    &Z80::Opc_fdxx_85,
    &Z80::Opc_fdxx_86,
    &Z80::invalid_opcode,	/* 0xfd87 */
    &Z80::invalid_opcode,	/* 0xfd88 */
    &Z80::invalid_opcode,	/* 0xfd89 */
    &Z80::invalid_opcode,	/* 0xfd8a */
    &Z80::invalid_opcode,	/* 0xfd8b */
    &Z80::Opc_fdxx_8c,
    &Z80::Opc_fdxx_8d,
    &Z80::Opc_fdxx_8e,
    &Z80::invalid_opcode,	/* 0xfd8f */
    &Z80::invalid_opcode,	/* 0xfd90 */
    &Z80::invalid_opcode,	/* 0xfd91 */
    &Z80::invalid_opcode,	/* 0xfd92 */
    &Z80::invalid_opcode,	/* 0xfd93 */
    &Z80::Opc_fdxx_94,
    &Z80::Opc_fdxx_95,
    &Z80::Opc_fdxx_96,
    &Z80::invalid_opcode,	/* 0xfd97 */
    &Z80::invalid_opcode,	/* 0xfd98 */
    &Z80::invalid_opcode,	/* 0xfd99 */
    &Z80::invalid_opcode,	/* 0xfd9a */
    &Z80::invalid_opcode,	/* 0xfd9b */
    &Z80::Opc_fdxx_9c,
    &Z80::Opc_fdxx_9d,
    &Z80::Opc_fdxx_9e,
    &Z80::invalid_opcode,	/* 0xfd9f */
    &Z80::invalid_opcode,	/* 0xfda0 */
    &Z80::invalid_opcode,	/* 0xfda1 */
    &Z80::invalid_opcode,	/* 0xfda2 */
    &Z80::invalid_opcode,	/* 0xfda3 */
    &Z80::Opc_fdxx_a4,
    &Z80::Opc_fdxx_a5,
    &Z80::Opc_fdxx_a6,
    &Z80::invalid_opcode,	/* 0xfda7 */
    &Z80::invalid_opcode,	/* 0xfda8 */
    &Z80::invalid_opcode,	/* 0xfda9 */
    &Z80::invalid_opcode,	/* 0xfdaa */
    &Z80::invalid_opcode,	/* 0xfdab */
    &Z80::Opc_fdxx_ac,
    &Z80::Opc_fdxx_ad,
    &Z80::Opc_fdxx_ae,
    &Z80::invalid_opcode,	/* 0xfdaf */
    &Z80::invalid_opcode,	/* 0xfdb0 */
    &Z80::invalid_opcode,	/* 0xfdb1 */
    &Z80::invalid_opcode,	/* 0xfdb2 */
    &Z80::invalid_opcode,	/* 0xfdb3 */
    &Z80::Opc_fdxx_b4,
    &Z80::Opc_fdxx_b5,
    &Z80::Opc_fdxx_b6,
    &Z80::invalid_opcode,	/* 0xfdb7 */
    &Z80::invalid_opcode,	/* 0xfdb8 */
    &Z80::invalid_opcode,	/* 0xfdb9 */
    &Z80::invalid_opcode,	/* 0xfdba */
    &Z80::invalid_opcode,	/* 0xfdbb */
    &Z80::Opc_fdxx_bc,
    &Z80::Opc_fdxx_bd,
    &Z80::Opc_fdxx_be,
    &Z80::invalid_opcode,	/* 0xfdbf */
    &Z80::invalid_opcode,	/* 0xfdc0 */
    &Z80::invalid_opcode,	/* 0xfdc1 */
    &Z80::invalid_opcode,	/* 0xfdc2 */
    &Z80::invalid_opcode,	/* 0xfdc3 */
    &Z80::invalid_opcode,	/* 0xfdc4 */
    &Z80::invalid_opcode,	/* 0xfdc5 */
    &Z80::invalid_opcode,	/* 0xfdc6 */
    &Z80::invalid_opcode,	/* 0xfdc7 */
    &Z80::invalid_opcode,	/* 0xfdc8 */
    &Z80::invalid_opcode,	/* 0xfdc9 */
    &Z80::invalid_opcode,	/* 0xfdca */
    &Z80::exec_fdcb,
    &Z80::invalid_opcode,	/* 0xfdcc */
    &Z80::invalid_opcode,	/* 0xfdcd */
    &Z80::invalid_opcode,	/* 0xfdce */
    &Z80::invalid_opcode,	/* 0xfdcf */
    &Z80::invalid_opcode,	/* 0xfdd0 */
    &Z80::invalid_opcode,	/* 0xfdd1 */
    &Z80::invalid_opcode,	/* 0xfdd2 */
    &Z80::invalid_opcode,	/* 0xfdd3 */
    &Z80::invalid_opcode,	/* 0xfdd4 */
    &Z80::invalid_opcode,	/* 0xfdd5 */
    &Z80::invalid_opcode,	/* 0xfdd6 */
    &Z80::invalid_opcode,	/* 0xfdd7 */
    &Z80::invalid_opcode,	/* 0xfdd8 */
    &Z80::invalid_opcode,	/* 0xfdd9 */
    &Z80::invalid_opcode,	/* 0xfdda */
    &Z80::invalid_opcode,	/* 0xfddb */
    &Z80::invalid_opcode,	/* 0xfddc */
    &Z80::invalid_opcode,	/* 0xfddd */
    &Z80::invalid_opcode,	/* 0xfdde */
    &Z80::invalid_opcode,	/* 0xfddf */
    &Z80::invalid_opcode,	/* 0xfde0 */
    &Z80::Opc_fdxx_e1,
    &Z80::invalid_opcode,	/* 0xfde2 */
    &Z80::Opc_fdxx_e3,
    &Z80::invalid_opcode,	/* 0xfde4 */
    &Z80::Opc_fdxx_e5,
    &Z80::invalid_opcode,	/* 0xfde6 */
    &Z80::invalid_opcode,	/* 0xfde7 */
    &Z80::invalid_opcode,	/* 0xfde8 */
    &Z80::Opc_fdxx_e9,
    &Z80::invalid_opcode,	/* 0xfdea */
    &Z80::invalid_opcode,	/* 0xfdeb */
    &Z80::invalid_opcode,	/* 0xfdec */
    &Z80::invalid_opcode,	/* 0xfded */
    &Z80::invalid_opcode,	/* 0xfdee */
    &Z80::invalid_opcode,	/* 0xfdef */
    &Z80::invalid_opcode,	/* 0xfdf0 */
    &Z80::invalid_opcode,	/* 0xfdf1 */
    &Z80::invalid_opcode,	/* 0xfdf2 */
    &Z80::invalid_opcode,	/* 0xfdf3 */
    &Z80::invalid_opcode,	/* 0xfdf4 */
    &Z80::invalid_opcode,	/* 0xfdf5 */
    &Z80::invalid_opcode,	/* 0xfdf6 */
    &Z80::invalid_opcode,	/* 0xfdf7 */
    &Z80::invalid_opcode,	/* 0xfdf8 */
    &Z80::Opc_fdxx_f9,
    &Z80::invalid_opcode,	/* 0xfdfa */
    &Z80::invalid_opcode,	/* 0xfdfb */
    &Z80::invalid_opcode,	/* 0xfdfc */
    &Z80::invalid_opcode,	/* 0xfdfd */
    &Z80::invalid_opcode,	/* 0xfdfe */
    &Z80::invalid_opcode	/* 0xfdff */
};
