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
 * File: Opc_dd.cpp
 *
 * Project: Oldspark emulator.
 *
 * Description: This class implements all opcodes with 0xdd prefixes.
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

void Z80::exec_dd()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    instruction =  env.rd8( PC++ );
    (this->*(Opc_ddxx[instruction]))();
#ifdef OPCODES_STATS
    DD_Prefix[ instruction ]++;
#endif
}

/* ADD IX, BC */
void Z80::Opc_ddxx_09()
{
    IX = add16(IX, getBC());
    cycleCount += 15;
}

/* ADD IX, DE */
void Z80::Opc_ddxx_19()
{
    IX = add16(IX, getDE());
    cycleCount += 15;
}

/* LD IX, (nn) */
void Z80::Opc_ddxx_21()
{
    IX = env.rd16(PC);
    PC+=2;
    cycleCount += 14;
}

/* LD (NN),IX */
void Z80::Opc_ddxx_22()
{
    setNNi16(IX);
    PC+=2;
    cycleCount += 20;
}

/* INC IX */
void Z80::Opc_ddxx_23()
{
    IX++;
    cycleCount += 10;
}

/* INC IXH */
void Z80::Opc_ddxx_24()
{
    IX = (IX & 0xFF) | (inc8(IX >> 8) << 8);
    cycleCount += 9;
}

/* DEC IXH */
void Z80::Opc_ddxx_25()
{
    IX = (IX & 0xFF) | (dec8(IX >> 8) << 8);
    cycleCount += 9;
}

/* LD IXH, n */
void Z80::Opc_ddxx_26()
{
    IX = ((IX & 0xFF) |  env.rd8(PC++) << 8);
    cycleCount += 9;
}

/* ADD IX, IX */
void Z80::Opc_ddxx_29()
{
    IX = add16(IX, IX);
    cycleCount += 15;
}

/* LD IX,(nn) */
void Z80::Opc_ddxx_2a()
{
    IX = getNNi16();
    PC += 2;
    cycleCount += 20;
}

/* DEC IX */
void Z80::Opc_ddxx_2b()
{
    IX--;
    cycleCount += 10;
}

/* INC IXL */
void Z80::Opc_ddxx_2c()
{
    IX = (IX & 0xFF00) | (inc8(IX & 0xFF));
    cycleCount += 9;
}

/* DEC IXL */
void Z80::Opc_ddxx_2d()
{
    IX = (IX & 0xFF00) | (dec8(IX & 0xFF));
    cycleCount += 9;
}

/* LD IXL, n */
void Z80::Opc_ddxx_2e()
{
    IX = (IX & 0xFF00) | env.rd8(PC++);
    cycleCount += 9;
}

/* INC (IX+d) */
void Z80::Opc_ddxx_34()
{
    setIXdi(inc8(getIXdi()));
    PC++;
    cycleCount += 23;
}

/* DEC (IX+d) */
void Z80::Opc_ddxx_35()
{
    setIXdi(dec8(getIXdi()));
    PC++;
    cycleCount += 23;
}

/* LD (IX+d), n */
void Z80::Opc_ddxx_36()
{
    setIXdi(env.rd8(PC+1));
    PC += 2;
    cycleCount += 19;
}

/* ADD IX, SP */
void Z80::Opc_ddxx_39()
{
    IX = add16(IX, SP);
    cycleCount += 15;
}

/* LD B, IXH */
void Z80::Opc_ddxx_44()
{
    B = (IX >> 8);
    cycleCount += 9;
}

/* LD B, IXL */
void Z80::Opc_ddxx_45()
{
    B = (IX & 0xFF);
    cycleCount += 9;
}

/* LD B, (IX+d) */
void Z80::Opc_ddxx_46()
{
    B = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD C, IXH */
void Z80::Opc_ddxx_4c()
{
    C = (IX >> 8);
    cycleCount += 9;
}

/* LD C, IXL */
void Z80::Opc_ddxx_4d()
{
    C = (IX & 0xFF);
    cycleCount += 9;
}

/* LD C, (IX+d) */
void Z80::Opc_ddxx_4e()
{
    C = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD D, IXH */
void Z80::Opc_ddxx_54()
{
    D = (IX >> 8);
    cycleCount += 9;
}

/* LD D, IXL */
void Z80::Opc_ddxx_55()
{
    D = (IX & 0xFF);
    cycleCount += 9;
}

/* LD D, (IX+d) */
void Z80::Opc_ddxx_56()
{
    D = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD E, IXH */
void Z80::Opc_ddxx_5c()
{
    E = (IX >> 8);
    cycleCount += 9;
}

/* LD E, IXL */
void Z80::Opc_ddxx_5d()
{
    E = (IX & 0xFF);
    cycleCount += 9;
}

/* LD E, (IX+d) */
void Z80::Opc_ddxx_5e()
{
    E = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD IXH, B */
void Z80::Opc_ddxx_60()
{
    IX = ( IX & 0xFF ) | (( u16 )B << 8 );
    cycleCount += 9;
}

/* LD IXH, C */
void Z80::Opc_ddxx_61()
{
    IX = ( IX & 0xFF ) | (( u16 )C << 8 );
    cycleCount += 9;
}

/* LD IXH, D */
void Z80::Opc_ddxx_62()
{
    IX = ( IX & 0xFF ) | (( u16 )D << 8 );
    cycleCount += 9;
}

/* LD IXH, E */
void Z80::Opc_ddxx_63()
{
    IX = ( IX & 0xFF ) | (( u16 )E << 8 );
    cycleCount += 9;
}

/* LD IXH, IXH */
void Z80::Opc_ddxx_64()
{
    IX = IX; // Do nothing;
    cycleCount += 9;
}

/* LD IXH, IXL */
void Z80::Opc_ddxx_65()
{
    IX = ( IX & 0xFF ) | (( IX & 0xFF ) << 8 );
    cycleCount += 9;
}

/* LD H, (IX+d) */
void Z80::Opc_ddxx_66()
{
    H = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD IXH, A */
void Z80::Opc_ddxx_67()
{
    IX = ( IX & 0xFF ) | (( u16 )A << 8 );
    cycleCount += 9;
}

/* LD IXL, B */
void Z80::Opc_ddxx_68()
{
    IX = ( IX & 0xFF00 ) | B;
    cycleCount += 9;
}

/* LD IXL, C */
void Z80::Opc_ddxx_69()
{
    IX = ( IX & 0xFF00 ) | C;
    cycleCount += 9;
}

/* LD IXL, D */
void Z80::Opc_ddxx_6a()
{
    IX = ( IX & 0xFF00 ) | D;
    cycleCount += 9;
}

/* LD IXL, E */
void Z80::Opc_ddxx_6b()
{
    IX = ( IX & 0xFF00 ) | E;
    cycleCount += 9;
}

/* LD IXL, IXH */
void Z80::Opc_ddxx_6c()
{
    IX = ( IX & 0xFF00 ) | ( IX >> 8 );
    cycleCount += 9;
}

/* LD IXL, IXL */
void Z80::Opc_ddxx_6d()
{
    IX = IX; // Do nothing;
    cycleCount += 9;
}

/* LD L, (IX+d) */
void Z80::Opc_ddxx_6e()
{
    L = getIXdi();
    PC++;
    cycleCount += 19;
}

/* LD IXL, A */
void Z80::Opc_ddxx_6f()
{
    IX = ( IX & 0xFF00 ) | A;
    cycleCount += 9;
}

/* LD (IX+d), B */
void Z80::Opc_ddxx_70()
{
    setIXdi(B);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), C */
void Z80::Opc_ddxx_71()
{
    setIXdi(C);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), D */
void Z80::Opc_ddxx_72()
{
    setIXdi(D);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), E */
void Z80::Opc_ddxx_73()
{
    setIXdi(E);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), H */
void Z80::Opc_ddxx_74()
{
    setIXdi(H);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), L */
void Z80::Opc_ddxx_75()
{
    setIXdi(L);
    PC++;
    cycleCount += 19;
}

/* LD (IX+d), A */
void Z80::Opc_ddxx_77()
{
    setIXdi(A);
    PC++;
    cycleCount += 19;
}

/* LD A, IXH */
void Z80::Opc_ddxx_7c()
{
    A = (IX >> 8);
    cycleCount += 9;
}

/* LD A, IXL */
void Z80::Opc_ddxx_7d()
{
    A = (IX & 0xFF);
    cycleCount += 9;
}

/* LD A, (IX+d) */
void Z80::Opc_ddxx_7e()
{
    A = getIXdi();
    PC++;
    cycleCount += 19;
}

/* ADD A, IXH */
void Z80::Opc_ddxx_84()
{
    A = add8(A, IX >> 8);
    cycleCount += 9;
}

/* ADD A, IXL */
void Z80::Opc_ddxx_85()
{
    A = add8(A, IX & 0xFF);
    cycleCount += 9;
}

/* ADD A, (IX+d) */
void Z80::Opc_ddxx_86()
{
    A = add8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* ADC A, IXH */
void Z80::Opc_ddxx_8c()
{
    A = adc8(A, IX >> 8);
    cycleCount += 9;
}

/* ADC A, IXL */
void Z80::Opc_ddxx_8d()
{
    A = adc8(A, IX & 0xFF);
    cycleCount += 9;
}

/* ADC A, (IX+d) */
void Z80::Opc_ddxx_8e()
{
    A = adc8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* SUB A, IXH */
void Z80::Opc_ddxx_94()
{
    A = sub8(A, IX >> 8);
    cycleCount += 9;
}

/* SUB A, IXL */
void Z80::Opc_ddxx_95()
{
    A = sub8(A, IX & 0xFF);
    cycleCount += 9;
}

/* SUB A, (IX+d) */
void Z80::Opc_ddxx_96()
{
    A = sub8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* SBC A, IXH */
void Z80::Opc_ddxx_9c()
{
    A = sbc8(A, IX >> 8);
    cycleCount += 9;
}

/* SBC A, IXL */
void Z80::Opc_ddxx_9d()
{
    A = sbc8(A, IX & 0xFF);
    cycleCount += 9;
}

/* SBC A, (IX+d) */
void Z80::Opc_ddxx_9e()
{
    A = sbc8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* AND A, IXH */
void Z80::Opc_ddxx_a4()
{
    A = and8(A, IX >> 8);
    cycleCount += 9;
}

/* AND A, IXL */
void Z80::Opc_ddxx_a5()
{
    A = and8(A, IX & 0xFF);
    cycleCount += 9;
}

/* AND A, (IX+d) */
void Z80::Opc_ddxx_a6()
{
    A = and8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* XOR A, IXH */
void Z80::Opc_ddxx_ac()
{
    A = xor8(A, IX >> 8);
    cycleCount += 9;
}

/* XOR A, IXL */
void Z80::Opc_ddxx_ad()
{
    A = xor8(A, IX & 0xFF);
    cycleCount += 9;
}

/* XOR A, (IX+d) */
void Z80::Opc_ddxx_ae()
{
    A = xor8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* OR A, IXH */
void Z80::Opc_ddxx_b4()
{
    A = or8(A, IX >> 8);
    cycleCount += 9;
}

/* OR A, IXL */
void Z80::Opc_ddxx_b5()
{
    A = or8(A, IX & 0xFF);
    cycleCount += 9;
}

/* OR A, (IX+d) */
void Z80::Opc_ddxx_b6()
{
    A = or8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* CP A, IXH */
void Z80::Opc_ddxx_bc()
{
    cp8(A, IX >> 8);
    cycleCount += 9;
}

/* CP A, IXL */
void Z80::Opc_ddxx_bd()
{
    cp8(A, IX & 0xFF);
    cycleCount += 9;
}

/* CP A, (IX+d) */
void Z80::Opc_ddxx_be()
{
    cp8(A, getIXdi());
    PC++;
    cycleCount += 19;
}

/* POP IX */
void Z80::Opc_ddxx_e1()
{
    IX = pop();
    cycleCount += 14;
}

/* EX (SP), IX */
void Z80::Opc_ddxx_e3()
{
    u16 tmp1 = env.rd16( SP );
    env.wr16( SP, IX );
    IX = tmp1;
    cycleCount += 23;
}

/* PUSH IX */
void Z80::Opc_ddxx_e5()
{
    push(IX);
    cycleCount += 15;
}

/* JP IX or LD PC, IX */
void Z80::Opc_ddxx_e9()
{
    PC = IX;
    cycleCount += 8;
}

/* LD SP, IX */
void Z80::Opc_ddxx_f9()
{
    SP = IX;
    cycleCount += 10;
}

Z80::Opc_handler Z80::Opc_ddxx[256] =
{
    &Z80::invalid_opcode,	/* 0xdd00 */
    &Z80::invalid_opcode,	/* 0xdd01 */
    &Z80::invalid_opcode,	/* 0xdd02 */
    &Z80::invalid_opcode,	/* 0xdd03 */
    &Z80::invalid_opcode,	/* 0xdd04 */
    &Z80::invalid_opcode,	/* 0xdd05 */
    &Z80::invalid_opcode,	/* 0xdd06 */
    &Z80::invalid_opcode,	/* 0xdd07 */
    &Z80::invalid_opcode,	/* 0xdd08 */
    &Z80::Opc_ddxx_09,
    &Z80::invalid_opcode,	/* 0xdd0a */
    &Z80::invalid_opcode,	/* 0xdd0b */
    &Z80::invalid_opcode,	/* 0xdd0c */
    &Z80::invalid_opcode,	/* 0xdd0d */
    &Z80::invalid_opcode,	/* 0xdd0e */
    &Z80::invalid_opcode,	/* 0xdd0f */
    &Z80::invalid_opcode,	/* 0xdd10 */
    &Z80::invalid_opcode,	/* 0xdd11 */
    &Z80::invalid_opcode,	/* 0xdd12 */
    &Z80::invalid_opcode,	/* 0xdd13 */
    &Z80::invalid_opcode,	/* 0xdd14 */
    &Z80::invalid_opcode,	/* 0xdd15 */
    &Z80::invalid_opcode,	/* 0xdd16 */
    &Z80::invalid_opcode,	/* 0xdd17 */
    &Z80::invalid_opcode,	/* 0xdd18 */
    &Z80::Opc_ddxx_19,
    &Z80::invalid_opcode,	/* 0xdd1a */
    &Z80::invalid_opcode,	/* 0xdd1b */
    &Z80::invalid_opcode,	/* 0xdd1c */
    &Z80::invalid_opcode,	/* 0xdd1d */
    &Z80::invalid_opcode,	/* 0xdd1e */
    &Z80::invalid_opcode,	/* 0xdd1f */
    &Z80::invalid_opcode,	/* 0xdd20 */
    &Z80::Opc_ddxx_21,
    &Z80::Opc_ddxx_22,
    &Z80::Opc_ddxx_23,
    &Z80::Opc_ddxx_24,
    &Z80::Opc_ddxx_25,
    &Z80::Opc_ddxx_26,
    &Z80::invalid_opcode,	/* 0xdd27 */
    &Z80::invalid_opcode,	/* 0xdd28 */
    &Z80::Opc_ddxx_29,
    &Z80::Opc_ddxx_2a,
    &Z80::Opc_ddxx_2b,
    &Z80::Opc_ddxx_2c,
    &Z80::Opc_ddxx_2d,
    &Z80::Opc_ddxx_2e,
    &Z80::invalid_opcode,	/* 0xdd2f */
    &Z80::invalid_opcode,	/* 0xdd30 */
    &Z80::invalid_opcode,	/* 0xdd31 */
    &Z80::invalid_opcode,	/* 0xdd32 */
    &Z80::invalid_opcode,	/* 0xdd33 */
    &Z80::Opc_ddxx_34,
    &Z80::Opc_ddxx_35,
    &Z80::Opc_ddxx_36,
    &Z80::invalid_opcode,	/* 0xdd37 */
    &Z80::invalid_opcode,	/* 0xdd38 */
    &Z80::Opc_ddxx_39,
    &Z80::invalid_opcode,	/* 0xdd3a */
    &Z80::invalid_opcode,	/* 0xdd3b */
    &Z80::invalid_opcode,	/* 0xdd3c */
    &Z80::invalid_opcode,	/* 0xdd3d */
    &Z80::invalid_opcode,	/* 0xdd3e */
    &Z80::invalid_opcode,	/* 0xdd3f */
    &Z80::invalid_opcode,	/* 0xdd40 */
    &Z80::invalid_opcode,	/* 0xdd41 */
    &Z80::invalid_opcode,	/* 0xdd42 */
    &Z80::invalid_opcode,	/* 0xdd43 */
    &Z80::Opc_ddxx_44,
    &Z80::Opc_ddxx_45,
    &Z80::Opc_ddxx_46,
    &Z80::invalid_opcode,	/* 0xdd47 */
    &Z80::invalid_opcode,	/* 0xdd48 */
    &Z80::invalid_opcode,	/* 0xdd49 */
    &Z80::invalid_opcode,	/* 0xdd4a */
    &Z80::invalid_opcode,	/* 0xdd4b */
    &Z80::Opc_ddxx_4c,
    &Z80::Opc_ddxx_4d,
    &Z80::Opc_ddxx_4e,
    &Z80::invalid_opcode,	/* 0xdd4f */
    &Z80::invalid_opcode,	/* 0xdd50 */
    &Z80::invalid_opcode,	/* 0xdd51 */
    &Z80::invalid_opcode,	/* 0xdd52 */
    &Z80::invalid_opcode,	/* 0xdd53 */
    &Z80::Opc_ddxx_54,
    &Z80::Opc_ddxx_55,
    &Z80::Opc_ddxx_56,
    &Z80::invalid_opcode,	/* 0xdd57 */
    &Z80::invalid_opcode,	/* 0xdd58 */
    &Z80::invalid_opcode,	/* 0xdd59 */
    &Z80::invalid_opcode,	/* 0xdd5a */
    &Z80::invalid_opcode,	/* 0xdd5b */
    &Z80::Opc_ddxx_5c,
    &Z80::Opc_ddxx_5d,
    &Z80::Opc_ddxx_5e,
    &Z80::invalid_opcode,	/* 0xdd5f */
    &Z80::Opc_ddxx_60,
    &Z80::Opc_ddxx_61,
    &Z80::Opc_ddxx_62,
    &Z80::Opc_ddxx_63,
    &Z80::Opc_ddxx_64,
    &Z80::Opc_ddxx_65,
    &Z80::Opc_ddxx_66,
    &Z80::Opc_ddxx_67,
    &Z80::Opc_ddxx_68,
    &Z80::Opc_ddxx_69,
    &Z80::Opc_ddxx_6a,
    &Z80::Opc_ddxx_6b,
    &Z80::Opc_ddxx_6c,
    &Z80::Opc_ddxx_6d,
    &Z80::Opc_ddxx_6e,
    &Z80::Opc_ddxx_6f,
    &Z80::Opc_ddxx_70,
    &Z80::Opc_ddxx_71,
    &Z80::Opc_ddxx_72,
    &Z80::Opc_ddxx_73,
    &Z80::Opc_ddxx_74,
    &Z80::Opc_ddxx_75,
    &Z80::invalid_opcode,	/* 0xdd76 */
    &Z80::Opc_ddxx_77,
    &Z80::invalid_opcode,	/* 0xdd78 */
    &Z80::invalid_opcode,	/* 0xdd79 */
    &Z80::invalid_opcode,	/* 0xdd7a */
    &Z80::invalid_opcode,	/* 0xdd7b */
    &Z80::Opc_ddxx_7c,
    &Z80::Opc_ddxx_7d,
    &Z80::Opc_ddxx_7e,
    &Z80::invalid_opcode,	/* 0xdd7f */
    &Z80::invalid_opcode,	/* 0xdd80 */
    &Z80::invalid_opcode,	/* 0xdd81 */
    &Z80::invalid_opcode,	/* 0xdd82 */
    &Z80::invalid_opcode,	/* 0xdd83 */
    &Z80::Opc_ddxx_84,
    &Z80::Opc_ddxx_85,
    &Z80::Opc_ddxx_86,
    &Z80::invalid_opcode,	/* 0xdd87 */
    &Z80::invalid_opcode,	/* 0xdd88 */
    &Z80::invalid_opcode,	/* 0xdd89 */
    &Z80::invalid_opcode,	/* 0xdd8a */
    &Z80::invalid_opcode,	/* 0xdd8b */
    &Z80::Opc_ddxx_8c,
    &Z80::Opc_ddxx_8d,
    &Z80::Opc_ddxx_8e,
    &Z80::invalid_opcode,	/* 0xdd8f */
    &Z80::invalid_opcode,	/* 0xdd90 */
    &Z80::invalid_opcode,	/* 0xdd91 */
    &Z80::invalid_opcode,	/* 0xdd92 */
    &Z80::invalid_opcode,	/* 0xdd93 */
    &Z80::Opc_ddxx_94,
    &Z80::Opc_ddxx_95,
    &Z80::Opc_ddxx_96,
    &Z80::invalid_opcode,	/* 0xdd97 */
    &Z80::invalid_opcode,	/* 0xdd98 */
    &Z80::invalid_opcode,	/* 0xdd99 */
    &Z80::invalid_opcode,	/* 0xdd9a */
    &Z80::invalid_opcode,	/* 0xdd9b */
    &Z80::Opc_ddxx_9c,
    &Z80::Opc_ddxx_9d,
    &Z80::Opc_ddxx_9e,
    &Z80::invalid_opcode,	/* 0xdd9f */
    &Z80::invalid_opcode,	/* 0xdda0 */
    &Z80::invalid_opcode,	/* 0xdda1 */
    &Z80::invalid_opcode,	/* 0xdda2 */
    &Z80::invalid_opcode,	/* 0xdda3 */
    &Z80::Opc_ddxx_a4,
    &Z80::Opc_ddxx_a5,
    &Z80::Opc_ddxx_a6,
    &Z80::invalid_opcode,	/* 0xdda7 */
    &Z80::invalid_opcode,	/* 0xdda8 */
    &Z80::invalid_opcode,	/* 0xdda9 */
    &Z80::invalid_opcode,	/* 0xddaa */
    &Z80::invalid_opcode,	/* 0xddab */
    &Z80::Opc_ddxx_ac,
    &Z80::Opc_ddxx_ad,
    &Z80::Opc_ddxx_ae,
    &Z80::invalid_opcode,	/* 0xddaf */
    &Z80::invalid_opcode,	/* 0xddb0 */
    &Z80::invalid_opcode,	/* 0xddb1 */
    &Z80::invalid_opcode,	/* 0xddb2 */
    &Z80::invalid_opcode,	/* 0xddb3 */
    &Z80::Opc_ddxx_b4,
    &Z80::Opc_ddxx_b5,
    &Z80::Opc_ddxx_b6,
    &Z80::invalid_opcode,	/* 0xddb7 */
    &Z80::invalid_opcode,	/* 0xddb8 */
    &Z80::invalid_opcode,	/* 0xddb9 */
    &Z80::invalid_opcode,	/* 0xddba */
    &Z80::invalid_opcode,	/* 0xddbb */
    &Z80::Opc_ddxx_bc,
    &Z80::Opc_ddxx_bd,
    &Z80::Opc_ddxx_be,
    &Z80::invalid_opcode,	/* 0xddbf */
    &Z80::invalid_opcode,	/* 0xddc0 */
    &Z80::invalid_opcode,	/* 0xddc1 */
    &Z80::invalid_opcode,	/* 0xddc2 */
    &Z80::invalid_opcode,	/* 0xddc3 */
    &Z80::invalid_opcode,	/* 0xddc4 */
    &Z80::invalid_opcode,	/* 0xddc5 */
    &Z80::invalid_opcode,	/* 0xddc6 */
    &Z80::invalid_opcode,	/* 0xddc7 */
    &Z80::invalid_opcode,	/* 0xddc8 */
    &Z80::invalid_opcode,	/* 0xddc9 */
    &Z80::invalid_opcode,	/* 0xddca */
    &Z80::exec_ddcb,
    &Z80::invalid_opcode,	/* 0xddcc */
    &Z80::invalid_opcode,	/* 0xddcd */
    &Z80::invalid_opcode,	/* 0xddce */
    &Z80::invalid_opcode,	/* 0xddcf */
    &Z80::invalid_opcode,	/* 0xddd0 */
    &Z80::invalid_opcode,	/* 0xddd1 */
    &Z80::invalid_opcode,	/* 0xddd2 */
    &Z80::invalid_opcode,	/* 0xddd3 */
    &Z80::invalid_opcode,	/* 0xddd4 */
    &Z80::invalid_opcode,	/* 0xddd5 */
    &Z80::invalid_opcode,	/* 0xddd6 */
    &Z80::invalid_opcode,	/* 0xddd7 */
    &Z80::invalid_opcode,	/* 0xddd8 */
    &Z80::invalid_opcode,	/* 0xddd9 */
    &Z80::invalid_opcode,	/* 0xddda */
    &Z80::invalid_opcode,	/* 0xdddb */
    &Z80::invalid_opcode,	/* 0xdddc */
    &Z80::invalid_opcode,	/* 0xdddd */
    &Z80::invalid_opcode,	/* 0xddde */
    &Z80::invalid_opcode,	/* 0xdddf */
    &Z80::invalid_opcode,	/* 0xdde0 */
    &Z80::Opc_ddxx_e1,
    &Z80::invalid_opcode,	/* 0xdde2 */
    &Z80::Opc_ddxx_e3,
    &Z80::invalid_opcode,	/* 0xdde4 */
    &Z80::Opc_ddxx_e5,
    &Z80::invalid_opcode,	/* 0xdde6 */
    &Z80::invalid_opcode,	/* 0xdde7 */
    &Z80::invalid_opcode,	/* 0xdde8 */
    &Z80::Opc_ddxx_e9,
    &Z80::invalid_opcode,	/* 0xddea */
    &Z80::invalid_opcode,	/* 0xddeb */
    &Z80::invalid_opcode,	/* 0xddec */
    &Z80::invalid_opcode,	/* 0xdded */
    &Z80::invalid_opcode,	/* 0xddee */
    &Z80::invalid_opcode,	/* 0xddef */
    &Z80::invalid_opcode,	/* 0xddf0 */
    &Z80::invalid_opcode,	/* 0xddf1 */
    &Z80::invalid_opcode,	/* 0xddf2 */
    &Z80::invalid_opcode,	/* 0xddf3 */
    &Z80::invalid_opcode,	/* 0xddf4 */
    &Z80::invalid_opcode,	/* 0xddf5 */
    &Z80::invalid_opcode,	/* 0xddf6 */
    &Z80::invalid_opcode,	/* 0xddf7 */
    &Z80::invalid_opcode,	/* 0xddf8 */
    &Z80::Opc_ddxx_f9,
    &Z80::invalid_opcode,	/* 0xddfa */
    &Z80::invalid_opcode,	/* 0xddfb */
    &Z80::invalid_opcode,	/* 0xddfc */
    &Z80::invalid_opcode,	/* 0xddfd */
    &Z80::invalid_opcode,	/* 0xddfe */
    &Z80::invalid_opcode	/* 0xddff */
};
