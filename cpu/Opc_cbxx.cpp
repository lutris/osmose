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
 * File: Opc_cbxx.cpp
 *
 * Project: Oldspark emulator.
 *
 * Description: This class implements all opcodes with 0xcb prefixes.
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

/* Opcodes prefixed with 0xCB */
void Z80::exec_cb()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    instruction = env.rd8( PC++ );
    (this->*(Opc_cbxx[instruction]))();
#ifdef OPCODES_STATS
    CB_Prefix[ instruction ]++;
#endif
}

/* RLC B */
void Z80::Opc_cbxx_00()
{
    B = rlc8( B );
    cycleCount += 8;
}

/* RLC C */
void Z80::Opc_cbxx_01()
{
    C = rlc8( C );
    cycleCount += 8;
}

/* RLC D */
void Z80::Opc_cbxx_02()
{
    D = rlc8( D );
    cycleCount += 8;
}

/* RLC E */
void Z80::Opc_cbxx_03()
{
    E = rlc8( E );
    cycleCount += 8;
}

/* RLC H */
void Z80::Opc_cbxx_04()
{
    H = rlc8( H );
    cycleCount += 8;
}

/* RLC L */
void Z80::Opc_cbxx_05()
{
    L = rlc8( L );
    cycleCount += 8;
}

/* RLC (HL) */
void Z80::Opc_cbxx_06()
{
    env.wr8( getHL(), rlc8( getHLi()));
    cycleCount += 15;
}

/* RLC A */
void Z80::Opc_cbxx_07()
{
    A = rlc8( A );
    cycleCount += 8;
}

/* RRC B */
void Z80::Opc_cbxx_08()
{
    B = rrc8( B );
    cycleCount += 8;
}

/* RRC C */
void Z80::Opc_cbxx_09()
{
    C = rrc8( C );
    cycleCount += 8;
}

/* RRC D */
void Z80::Opc_cbxx_0a()
{
    D = rrc8( D );
    cycleCount += 8;
}

/* RRC E */
void Z80::Opc_cbxx_0b()
{
    E = rrc8( E );
    cycleCount += 8;
}

/* RRC H */
void Z80::Opc_cbxx_0c()
{
    H = rrc8( H );
    cycleCount += 8;
}

/* RRC L */
void Z80::Opc_cbxx_0d()
{
    L = rrc8( L );
    cycleCount += 8;
}

/* RRC (HL) */
void Z80::Opc_cbxx_0e()
{
    env.wr8( getHL(), rrc8( getHLi()));
    cycleCount += 15;
}

/* RRC A */
void Z80::Opc_cbxx_0f()
{
    A = rrc8( A );
    cycleCount += 8;
}

/* RL B */
void Z80::Opc_cbxx_10()
{
    B = rl8( B );
    cycleCount += 8;
}

/* RL C */
void Z80::Opc_cbxx_11()
{
    C = rl8( C );
    cycleCount += 8;
}

/* RL D */
void Z80::Opc_cbxx_12()
{
    D = rl8( D );
    cycleCount += 8;
}

/* RL E */
void Z80::Opc_cbxx_13()
{
    E = rl8( E );
    cycleCount += 8;
}

/* RL H */
void Z80::Opc_cbxx_14()
{
    H = rl8( H );
    cycleCount += 8;
}

/* RL L */
void Z80::Opc_cbxx_15()
{
    L = rl8( L );
    cycleCount += 8;
}

/* RL (HL) */
void Z80::Opc_cbxx_16()
{
    env.wr8( getHL(), rl8( getHLi()));
    cycleCount += 15;
}

/* RL A */
void Z80::Opc_cbxx_17()
{
    A = rl8( A );
    cycleCount += 8;
}

/* RR B */
void Z80::Opc_cbxx_18()
{
    B = rr8( B );
    cycleCount += 8;
}

/* RR C */
void Z80::Opc_cbxx_19()
{
    C = rr8( C );
    cycleCount += 8;
}

/* RR D */
void Z80::Opc_cbxx_1a()
{
    D = rr8( D );
    cycleCount += 8;
}

/* RR E */
void Z80::Opc_cbxx_1b()
{
    E = rr8( E );
    cycleCount += 8;
}

/* RR H */
void Z80::Opc_cbxx_1c()
{
    H = rr8( H );
    cycleCount += 8;
}

/* RR L */
void Z80::Opc_cbxx_1d()
{
    L = rr8( L );
    cycleCount += 8;
}

/* RR (HL) */
void Z80::Opc_cbxx_1e()
{
    env.wr8( getHL(), rr8( getHLi()));
    cycleCount += 15;
}

/* RR A */
void Z80::Opc_cbxx_1f()
{
    A = rr8( A );
    cycleCount += 8;
}

/* SLA B */
void Z80::Opc_cbxx_20()
{
    B = sla8( B );
    cycleCount += 8;
}

/* SLA C */
void Z80::Opc_cbxx_21()
{
    C = sla8( C );
    cycleCount += 8;
}

/* SLA D */
void Z80::Opc_cbxx_22()
{
    D = sla8( D );
    cycleCount += 8;
}

/* SLA E */
void Z80::Opc_cbxx_23()
{
    E = sla8( E );
    cycleCount += 8;
}

/* SLA H */
void Z80::Opc_cbxx_24()
{
    H = sla8( H );
    cycleCount += 8;
}

/* SLA L */
void Z80::Opc_cbxx_25()
{
    L = sla8( L );
    cycleCount += 8;
}

/* SLA (HL) */
void Z80::Opc_cbxx_26()
{
    env.wr8( getHL(), sla8( getHLi()));
    cycleCount += 15;
}

/* SLA A */
void Z80::Opc_cbxx_27()
{
    A = sla8( A );
    cycleCount += 8;
}

/* SRA B */
void Z80::Opc_cbxx_28()
{
    B = sra8( B );
    cycleCount += 8;
}

/* SRA C */
void Z80::Opc_cbxx_29()
{
    C = sra8( C );
    cycleCount += 8;
}

/* SRA D */
void Z80::Opc_cbxx_2a()
{
    D = sra8( D );
    cycleCount += 8;
}

/* SRA E */
void Z80::Opc_cbxx_2b()
{
    E = sra8( E );
    cycleCount += 8;
}

/* SRA H */
void Z80::Opc_cbxx_2c()
{
    H = sra8( H );
    cycleCount += 8;
}

/* SRA L */
void Z80::Opc_cbxx_2d()
{
    L = sra8( L );
    cycleCount += 8;
}

/* SRA (HL) */
void Z80::Opc_cbxx_2e()
{
    env.wr8( getHL(), sra8( getHLi()));
    cycleCount += 15;
}

/* SRA A */
void Z80::Opc_cbxx_2f()
{
    A = sra8( A );
    cycleCount += 8;
}

/* SLL B */
void Z80::Opc_cbxx_30()
{
    B = sll8( B );
    cycleCount += 8;
}

/* SLL C */
void Z80::Opc_cbxx_31()
{
    C = sll8( C );
    cycleCount += 8;
}

/* SLL D */
void Z80::Opc_cbxx_32()
{
    D = sll8( D );
    cycleCount += 8;
}

/* SLL E */
void Z80::Opc_cbxx_33()
{
    E = sll8( E );
    cycleCount += 8;
}

/* SLL H */
void Z80::Opc_cbxx_34()
{
    H = sll8( H );
    cycleCount += 8;
}

/* SLL L */
void Z80::Opc_cbxx_35()
{
    L = sll8( L );
    cycleCount += 8;
}

/* SLL (HL) */
void Z80::Opc_cbxx_36()
{
    env.wr8( getHL(), sll8( getHLi()));
    cycleCount += 15;
}

/* SLL A */
void Z80::Opc_cbxx_37()
{
    A = sll8( A );
    cycleCount += 8;
}

/* SRL B */
void Z80::Opc_cbxx_38()
{
    B = srl8( B );
    cycleCount += 8;
}

/* SRL C */
void Z80::Opc_cbxx_39()
{
    C = srl8( C );
    cycleCount += 8;
}

/* SRL D */
void Z80::Opc_cbxx_3a()
{
    D = srl8( D );
    cycleCount += 8;
}

/* SRL E */
void Z80::Opc_cbxx_3b()
{
    E = srl8( E );
    cycleCount += 8;
}

/* SRL H */
void Z80::Opc_cbxx_3c()
{
    H = srl8( H );
    cycleCount += 8;
}

/* SRL L */
void Z80::Opc_cbxx_3d()
{
    L = srl8( L );
    cycleCount += 8;
}

/* SRL (HL) */
void Z80::Opc_cbxx_3e()
{
    env.wr8( getHL(), srl8( getHLi()));
    cycleCount += 15;
}

/* SRL A */
void Z80::Opc_cbxx_3f()
{
    A = srl8( A );
    cycleCount += 8;
}

/* BIT 0, B */
void Z80::Opc_cbxx_40()
{
    bit(0, B);
    cycleCount += 8;
}

/* BIT 0, C */
void Z80::Opc_cbxx_41()
{
    bit(0, C);
    cycleCount += 8;
}

/* BIT 0, D */
void Z80::Opc_cbxx_42()
{
    bit(0, D);
    cycleCount += 8;
}

/* BIT 0, E */
void Z80::Opc_cbxx_43()
{
    bit(0, E);
    cycleCount += 8;
}

/* BIT 0, H */
void Z80::Opc_cbxx_44()
{
    bit(0, H);
    cycleCount += 8;
}

/* BIT 0, L */
void Z80::Opc_cbxx_45()
{
    bit(0, L);
    cycleCount += 8;
}

/* BIT 0, (HL) */
void Z80::Opc_cbxx_46()
{
    bit(0, getHLi());
    cycleCount += 12;
}

/* BIT 0, A */
void Z80::Opc_cbxx_47()
{
    bit(0, A);
    cycleCount += 8;
}

/* BIT 1, B */
void Z80::Opc_cbxx_48()
{
    bit(1, B);
    cycleCount += 8;
}

/* BIT 1, C */
void Z80::Opc_cbxx_49()
{
    bit(1, C);
    cycleCount += 8;
}

/* BIT 1, D */
void Z80::Opc_cbxx_4a()
{
    bit(1, D);
    cycleCount += 8;
}

/* BIT 1, E */
void Z80::Opc_cbxx_4b()
{
    bit(1, E);
    cycleCount += 8;
}

/* BIT 1, H */
void Z80::Opc_cbxx_4c()
{
    bit(1, H);
    cycleCount += 8;
}

/* BIT 1, L */
void Z80::Opc_cbxx_4d()
{
    bit(1, L);
    cycleCount += 8;
}

/* BIT 1, (HL) */
void Z80::Opc_cbxx_4e()
{
    bit(1, getHLi());
    cycleCount += 12;
}

/* BIT 1, A */
void Z80::Opc_cbxx_4f()
{
    bit(1, A);
    cycleCount += 8;
}

/* BIT 2, B */
void Z80::Opc_cbxx_50()
{
    bit(2, B);
    cycleCount += 8;
}

/* BIT 2, C */
void Z80::Opc_cbxx_51()
{
    bit(2, C);
    cycleCount += 8;
}

/* BIT 2, D */
void Z80::Opc_cbxx_52()
{
    bit(2, D);
    cycleCount += 8;
}

/* BIT 2, E */
void Z80::Opc_cbxx_53()
{
    bit(2, E);
    cycleCount += 8;
}

/* BIT 2, H */
void Z80::Opc_cbxx_54()
{
    bit(2, H);
    cycleCount += 8;
}

/* BIT 2, L */
void Z80::Opc_cbxx_55()
{
    bit(2, L);
    cycleCount += 8;
}

/* BIT 2, (HL) */
void Z80::Opc_cbxx_56()
{
    bit(2, getHLi());
    cycleCount += 12;
}

/* BIT 2, A */
void Z80::Opc_cbxx_57()
{
    bit(2, A);
    cycleCount += 8;
}

/* BIT 3, B */
void Z80::Opc_cbxx_58()
{
    bit(3, B);
    cycleCount += 8;
}

/* BIT 3, C */
void Z80::Opc_cbxx_59()
{
    bit(3, C);
    cycleCount += 8;
}

/* BIT 3, D */
void Z80::Opc_cbxx_5a()
{
    bit(3, D);
    cycleCount += 8;
}

/* BIT 3, E */
void Z80::Opc_cbxx_5b()
{
    bit(3, E);
    cycleCount += 8;
}

/* BIT 3, H */
void Z80::Opc_cbxx_5c()
{
    bit(3, H);
    cycleCount += 8;
}

/* BIT 3, L */
void Z80::Opc_cbxx_5d()
{
    bit(3, L);
    cycleCount += 8;
}

/* BIT 3, (HL) */
void Z80::Opc_cbxx_5e()
{
    bit(3, getHLi());
    cycleCount += 12;
}

/* BIT 3, A */
void Z80::Opc_cbxx_5f()
{
    bit(3, A);
    cycleCount += 8;
}

/* BIT 4, B */
void Z80::Opc_cbxx_60()
{
    bit(4, B);
    cycleCount += 8;
}

/* BIT 4, C */
void Z80::Opc_cbxx_61()
{
    bit(4, C);
    cycleCount += 8;
}

/* BIT 4, D */
void Z80::Opc_cbxx_62()
{
    bit(4, D);
    cycleCount += 8;
}

/* BIT 4, E */
void Z80::Opc_cbxx_63()
{
    bit(4, E);
    cycleCount += 8;
}

/* BIT 4, H */
void Z80::Opc_cbxx_64()
{
    bit(4, H);
    cycleCount += 8;
}

/* BIT 4, L */
void Z80::Opc_cbxx_65()
{
    bit(4, L);
    cycleCount += 8;
}

/* BIT 4, (HL) */
void Z80::Opc_cbxx_66()
{
    bit(4, getHLi());
    cycleCount += 12;
}

/* BIT 4, A */
void Z80::Opc_cbxx_67()
{
    bit(4, A);
    cycleCount += 8;
}

/* BIT 5, B */
void Z80::Opc_cbxx_68()
{
    bit(5, B);
    cycleCount += 8;
}

/* BIT 5, C */
void Z80::Opc_cbxx_69()
{
    bit(5, C);
    cycleCount += 8;
}

/* BIT 5, D */
void Z80::Opc_cbxx_6a()
{
    bit(5, D);
    cycleCount += 8;
}

/* BIT 5, E */
void Z80::Opc_cbxx_6b()
{
    bit(5, E);
    cycleCount += 8;
}

/* BIT 5, H */
void Z80::Opc_cbxx_6c()
{
    bit(5, H);
    cycleCount += 8;
}

/* BIT 5, L */
void Z80::Opc_cbxx_6d()
{
    bit(5, L);
    cycleCount += 8;
}

/* BIT 5, (HL) */
void Z80::Opc_cbxx_6e()
{
    bit(5, getHLi());
    cycleCount += 12;
}

/* BIT 5, A */
void Z80::Opc_cbxx_6f()
{
    bit(5, A);
    cycleCount += 8;
}

/* BIT 6, B */
void Z80::Opc_cbxx_70()
{
    bit(6, B);
    cycleCount += 8;
}

/* BIT 6, C */
void Z80::Opc_cbxx_71()
{
    bit(6, C);
    cycleCount += 8;
}

/* BIT 6, D */
void Z80::Opc_cbxx_72()
{
    bit(6, D);
    cycleCount += 8;
}

/* BIT 6, E */
void Z80::Opc_cbxx_73()
{
    bit(6, E);
    cycleCount += 8;
}

/* BIT 6, H */
void Z80::Opc_cbxx_74()
{
    bit(6, H);
    cycleCount += 8;
}

/* BIT 6, L */
void Z80::Opc_cbxx_75()
{
    bit(6, L);
    cycleCount += 8;
}

/* BIT 6, (HL) */
void Z80::Opc_cbxx_76()
{
    bit(6, getHLi());
    cycleCount += 12;
}

/* BIT 6, A */
void Z80::Opc_cbxx_77()
{
    bit(6, A);
    cycleCount += 8;
}

/* BIT 7, B */
void Z80::Opc_cbxx_78()
{
    bit(7, B);
    cycleCount += 8;
}

/* BIT 7, C */
void Z80::Opc_cbxx_79()
{
    bit(7, C);
    cycleCount += 8;
}

/* BIT 7, D */
void Z80::Opc_cbxx_7a()
{
    bit(7, D);
    cycleCount += 8;
}

/* BIT 7, E */
void Z80::Opc_cbxx_7b()
{
    bit(7, E);
    cycleCount += 8;
}

/* BIT 7, H */
void Z80::Opc_cbxx_7c()
{
    bit(7, H);
    cycleCount += 8;
}

/* BIT 7, L */
void Z80::Opc_cbxx_7d()
{
    bit(7, L);
    cycleCount += 8;
}

/* BIT 7, (HL) */
void Z80::Opc_cbxx_7e()
{
    bit(7, getHLi());
    cycleCount += 12;
}

/* BIT 7, A */
void Z80::Opc_cbxx_7f()
{
    bit(7, A);
    cycleCount += 8;
}

/* RES 0, B */
void Z80::Opc_cbxx_80()
{
    B = res(0, B);
    cycleCount += 8;
}

/* RES 0, C */
void Z80::Opc_cbxx_81()
{
    C = res(0, C);
    cycleCount += 8;
}

/* RES 0, D */
void Z80::Opc_cbxx_82()
{
    D = res(0, D);
    cycleCount += 8;
}

/* RES 0, E */
void Z80::Opc_cbxx_83()
{
    E = res(0, E);
    cycleCount += 8;
}

/* RES 0, H */
void Z80::Opc_cbxx_84()
{
    H = res(0, H);
    cycleCount += 8;
}

/* RES 0, L */
void Z80::Opc_cbxx_85()
{
    L = res(0, L);
    cycleCount += 8;
}

/* RES 0, (HL) */
void Z80::Opc_cbxx_86()
{
    setHLi(res(0, getHLi()));
    cycleCount += 15;
}

/* RES 0, A */
void Z80::Opc_cbxx_87()
{
    A = res(0, A);
    cycleCount += 8;
}

/* RES 1, B */
void Z80::Opc_cbxx_88()
{
    B = res(1, B);
    cycleCount += 8;
}

/* RES 1, C */
void Z80::Opc_cbxx_89()
{
    C = res(1, C);
    cycleCount += 8;
}

/* RES 1, D */
void Z80::Opc_cbxx_8a()
{
    D = res(1, D);
    cycleCount += 8;
}

/* RES 1, E */
void Z80::Opc_cbxx_8b()
{
    E = res(1, E);
    cycleCount += 8;
}

/* RES 1, H */
void Z80::Opc_cbxx_8c()
{
    H = res(1, H);
    cycleCount += 8;
}

/* RES 1, L */
void Z80::Opc_cbxx_8d()
{
    L = res(1, L);
    cycleCount += 8;
}

/* RES 1, (HL) */
void Z80::Opc_cbxx_8e()
{
    setHLi(res(1, getHLi()));
    cycleCount += 15;
}

/* RES 1, A */
void Z80::Opc_cbxx_8f()
{
    A = res(1, A);
    cycleCount += 8;
}

/* RES 2, B */
void Z80::Opc_cbxx_90()
{
    B = res(2, B);
    cycleCount += 8;
}

/* RES 2, C */
void Z80::Opc_cbxx_91()
{
    C = res(2, C);
    cycleCount += 8;
}

/* RES 2, D */
void Z80::Opc_cbxx_92()
{
    D = res(2, D);
    cycleCount += 8;
}

/* RES 2, E */
void Z80::Opc_cbxx_93()
{
    E = res(2, E);
    cycleCount += 8;
}

/* RES 2, H */
void Z80::Opc_cbxx_94()
{
    H = res(2, H);
    cycleCount += 8;
}

/* RES 2, L */
void Z80::Opc_cbxx_95()
{
    L = res(2, L);
    cycleCount += 8;
}

/* RES 2, (HL) */
void Z80::Opc_cbxx_96()
{
    setHLi(res(2, getHLi()));
    cycleCount += 15;
}

/* RES 2, A */
void Z80::Opc_cbxx_97()
{
    A = res(2, A);
    cycleCount += 8;
}

/* RES 3, B */
void Z80::Opc_cbxx_98()
{
    B = res(3, B);
    cycleCount += 8;
}

/* RES 3, C */
void Z80::Opc_cbxx_99()
{
    C = res(3, C);
    cycleCount += 8;
}

/* RES 3, D */
void Z80::Opc_cbxx_9a()
{
    D = res(3, D);
    cycleCount += 8;
}

/* RES 3, E */
void Z80::Opc_cbxx_9b()
{
    E = res(3, E);
    cycleCount += 8;
}

/* RES 3, H */
void Z80::Opc_cbxx_9c()
{
    H = res(3, H);
    cycleCount += 8;
}

/* RES 3, L */
void Z80::Opc_cbxx_9d()
{
    L = res(3, L);
    cycleCount += 8;
}

/* RES 3, (HL) */
void Z80::Opc_cbxx_9e()
{
    setHLi(res(3, getHLi()));
    cycleCount += 15;
}

/* RES 3, A */
void Z80::Opc_cbxx_9f()
{
    A = res(3, A);
    cycleCount += 8;
}

/* RES 4, B */
void Z80::Opc_cbxx_a0()
{
    B = res(4, B);
    cycleCount += 8;
}

/* RES 4, C */
void Z80::Opc_cbxx_a1()
{
    C = res(4, C);
    cycleCount += 8;
}

/* RES 4, D */
void Z80::Opc_cbxx_a2()
{
    D = res(4, D);
    cycleCount += 8;
}

/* RES 4, E */
void Z80::Opc_cbxx_a3()
{
    E = res(4, E);
    cycleCount += 8;
}

/* RES 4, H */
void Z80::Opc_cbxx_a4()
{
    H = res(4, H);
    cycleCount += 8;
}

/* RES 4, L */
void Z80::Opc_cbxx_a5()
{
    L = res(4, L);
    cycleCount += 8;
}

/* RES 4, (HL) */
void Z80::Opc_cbxx_a6()
{
    setHLi(res(4, getHLi()));
    cycleCount += 15;
}

/* RES 4, A */
void Z80::Opc_cbxx_a7()
{
    A = res(4, A);
    cycleCount += 8;
}

/* RES 5, B */
void Z80::Opc_cbxx_a8()
{
    B = res(5, B);
    cycleCount += 8;
}

/* RES 5, C */
void Z80::Opc_cbxx_a9()
{
    C = res(5, C);
    cycleCount += 8;
}

/* RES 5, D */
void Z80::Opc_cbxx_aa()
{
    D = res(5, D);
    cycleCount += 8;
}

/* RES 5, E */
void Z80::Opc_cbxx_ab()
{
    E = res(5, E);
    cycleCount += 8;
}

/* RES 5, H */
void Z80::Opc_cbxx_ac()
{
    H = res(5, H);
    cycleCount += 8;
}

/* RES 5, L */
void Z80::Opc_cbxx_ad()
{
    L = res(5, L);
    cycleCount += 8;
}

/* RES 5, (HL) */
void Z80::Opc_cbxx_ae()
{
    setHLi(res(5, getHLi()));
    cycleCount += 15;
}

/* RES 5, A */
void Z80::Opc_cbxx_af()
{
    A = res(5, A);
    cycleCount += 8;
}

/* RES 6, B */
void Z80::Opc_cbxx_b0()
{
    B = res(6, B);
    cycleCount += 8;
}

/* RES 6, C */
void Z80::Opc_cbxx_b1()
{
    C = res(6, C);
    cycleCount += 8;
}

/* RES 6, D */
void Z80::Opc_cbxx_b2()
{
    D = res(6, D);
    cycleCount += 8;
}

/* RES 6, E */
void Z80::Opc_cbxx_b3()
{
    E = res(6, E);
    cycleCount += 8;
}

/* RES 6, H */
void Z80::Opc_cbxx_b4()
{
    H = res(6, H);
    cycleCount += 8;
}

/* RES 6, L */
void Z80::Opc_cbxx_b5()
{
    L = res(6, L);
    cycleCount += 8;
}

/* RES 6, (HL) */
void Z80::Opc_cbxx_b6()
{
    setHLi(res(6, getHLi()));
    cycleCount += 15;
}

/* RES 6, A */
void Z80::Opc_cbxx_b7()
{
    A = res(6, A);
    cycleCount += 8;
}

/* RES 7, B */
void Z80::Opc_cbxx_b8()
{
    B = res(7, B);
    cycleCount += 8;
}

/* RES 7, C */
void Z80::Opc_cbxx_b9()
{
    C = res(7, C);
    cycleCount += 8;
}

/* RES 7, D */
void Z80::Opc_cbxx_ba()
{
    D = res(7, D);
    cycleCount += 8;
}

/* RES 7, E */
void Z80::Opc_cbxx_bb()
{
    E = res(7, E);
    cycleCount += 8;
}

/* RES 7, H */
void Z80::Opc_cbxx_bc()
{
    H = res(7, H);
    cycleCount += 8;
}

/* RES 7, L */
void Z80::Opc_cbxx_bd()
{
    L = res(7, L);
    cycleCount += 8;
}

/* RES 7, (HL) */
void Z80::Opc_cbxx_be()
{
    setHLi(res(7, getHLi()));
    cycleCount += 15;
}

/* RES 7, A */
void Z80::Opc_cbxx_bf()
{
    A = res(7, A);
    cycleCount += 8;
}

/* SET 0, B */
void Z80::Opc_cbxx_c0()
{
    B = set(0, B);
    cycleCount += 8;
}

/* SET 0, C */
void Z80::Opc_cbxx_c1()
{
    C = set(0, C);
    cycleCount += 8;
}

/* SET 0, D */
void Z80::Opc_cbxx_c2()
{
    D = set(0, D);
    cycleCount += 8;
}

/* SET 0, E */
void Z80::Opc_cbxx_c3()
{
    E = set(0, E);
    cycleCount += 8;
}

/* SET 0, H */
void Z80::Opc_cbxx_c4()
{
    H = set(0, H);
    cycleCount += 8;
}

/* SET 0, L */
void Z80::Opc_cbxx_c5()
{
    L = set(0, L);
    cycleCount += 8;
}

/* SET 0, (HL) */
void Z80::Opc_cbxx_c6()
{
    setHLi(set(0, getHLi()));
    cycleCount += 15;
}

/* SET 0, A */
void Z80::Opc_cbxx_c7()
{
    A = set(0, A);
    cycleCount += 8;
}

/* SET 1, B */
void Z80::Opc_cbxx_c8()
{
    B = set(1, B);
    cycleCount += 8;
}

/* SET 1, C */
void Z80::Opc_cbxx_c9()
{
    C = set(1, C);
    cycleCount += 8;
}

/* SET 1, D */
void Z80::Opc_cbxx_ca()
{
    D = set(1, D);
    cycleCount += 8;
}

/* SET 1, E */
void Z80::Opc_cbxx_cb()
{
    E = set(1, E);
    cycleCount += 8;
}

/* SET 1, H */
void Z80::Opc_cbxx_cc()
{
    H = set(1, H);
    cycleCount += 8;
}

/* SET 1, L */
void Z80::Opc_cbxx_cd()
{
    L = set(1, L);
    cycleCount += 8;
}

/* SET 1, (HL) */
void Z80::Opc_cbxx_ce()
{
    setHLi(set(1, getHLi()));
    cycleCount += 15;
}

/* SET 1, A */
void Z80::Opc_cbxx_cf()
{
    A = set(1, A);
    cycleCount += 8;
}

/* SET 2, B */
void Z80::Opc_cbxx_d0()
{
    B = set(2, B);
    cycleCount += 8;
}

/* SET 2, C */
void Z80::Opc_cbxx_d1()
{
    C = set(2, C);
    cycleCount += 8;
}

/* SET 2, D */
void Z80::Opc_cbxx_d2()
{
    D = set(2, D);
    cycleCount += 8;
}

/* SET 2, E */
void Z80::Opc_cbxx_d3()
{
    E = set(2, E);
    cycleCount += 8;
}

/* SET 2, H */
void Z80::Opc_cbxx_d4()
{
    H = set(2, H);
    cycleCount += 8;
}

/* SET 2, L */
void Z80::Opc_cbxx_d5()
{
    L = set(2, L);
    cycleCount += 8;
}

/* SET 2, (HL) */
void Z80::Opc_cbxx_d6()
{
    setHLi(set(2, getHLi()));
    cycleCount += 15;
}

/* SET 2, A */
void Z80::Opc_cbxx_d7()
{
    A = set(2, A);
    cycleCount += 8;
}

/* SET 3, B */
void Z80::Opc_cbxx_d8()
{
    B = set(3, B);
    cycleCount += 8;
}

/* SET 3, C */
void Z80::Opc_cbxx_d9()
{
    C = set(3, C);
    cycleCount += 8;
}

/* SET 3, D */
void Z80::Opc_cbxx_da()
{
    D = set(3, D);
    cycleCount += 8;
}

/* SET 3, E */
void Z80::Opc_cbxx_db()
{
    E = set(3, E);
    cycleCount += 8;
}

/* SET 3, H */
void Z80::Opc_cbxx_dc()
{
    H = set(3, H);
    cycleCount += 8;
}

/* SET 3, L */
void Z80::Opc_cbxx_dd()
{
    L = set(3, L);
    cycleCount += 8;
}

/* SET 3, (HL) */
void Z80::Opc_cbxx_de()
{
    setHLi(set(3, getHLi()));
    cycleCount += 15;
}

/* SET 3, A */
void Z80::Opc_cbxx_df()
{
    A = set(3, A);
    cycleCount += 8;
}

/* SET 4, B */
void Z80::Opc_cbxx_e0()
{
    B = set(4, B);
    cycleCount += 8;
}

/* SET 4, C */
void Z80::Opc_cbxx_e1()
{
    C = set(4, C);
    cycleCount += 8;
}

/* SET 4, D */
void Z80::Opc_cbxx_e2()
{
    D = set(4, D);
    cycleCount += 8;
}

/* SET 4, E */
void Z80::Opc_cbxx_e3()
{
    E = set(4, E);
    cycleCount += 8;
}

/* SET 4, H */
void Z80::Opc_cbxx_e4()
{
    H = set(4, H);
    cycleCount += 8;
}

/* SET 4, L */
void Z80::Opc_cbxx_e5()
{
    L = set(4, L);
    cycleCount += 8;
}

/* SET 4, (HL) */
void Z80::Opc_cbxx_e6()
{
    setHLi(set(4, getHLi()));
    cycleCount += 15;
}

/* SET 4, A */
void Z80::Opc_cbxx_e7()
{
    A = set(4, A);
    cycleCount += 8;
}

/* SET 5, B */
void Z80::Opc_cbxx_e8()
{
    B = set(5, B);
    cycleCount += 8;
}

/* SET 5, C */
void Z80::Opc_cbxx_e9()
{
    C = set(5, C);
    cycleCount += 8;
}

/* SET 5, D */
void Z80::Opc_cbxx_ea()
{
    D = set(5, D);
    cycleCount += 8;
}

/* SET 5, E */
void Z80::Opc_cbxx_eb()
{
    E = set(5, E);
    cycleCount += 8;
}

/* SET 5, H */
void Z80::Opc_cbxx_ec()
{
    H = set(5, H);
    cycleCount += 8;
}

/* SET 5, L */
void Z80::Opc_cbxx_ed()
{
    L = set(5, L);
    cycleCount += 8;
}

/* SET 5, (HL) */
void Z80::Opc_cbxx_ee()
{
    setHLi(set(5, getHLi()));
    cycleCount += 15;
}

/* SET 5, A */
void Z80::Opc_cbxx_ef()
{
    A = set(5, A);
    cycleCount += 8;
}

/* SET 6, B */
void Z80::Opc_cbxx_f0()
{
    B = set(6, B);
    cycleCount += 8;
}

/* SET 6, C */
void Z80::Opc_cbxx_f1()
{
    C = set(6, C);
    cycleCount += 8;
}

/* SET 6, D */
void Z80::Opc_cbxx_f2()
{
    D = set(6, D);
    cycleCount += 8;
}

/* SET 6, E */
void Z80::Opc_cbxx_f3()
{
    E = set(6, E);
    cycleCount += 8;
}

/* SET 6, H */
void Z80::Opc_cbxx_f4()
{
    H = set(6, H);
    cycleCount += 8;
}

/* SET 6, L */
void Z80::Opc_cbxx_f5()
{
    L = set(6, L);
    cycleCount += 8;
}

/* SET 6, (HL) */
void Z80::Opc_cbxx_f6()
{
    setHLi(set(6, getHLi()));
    cycleCount += 15;
}

/* SET 6, A */
void Z80::Opc_cbxx_f7()
{
    A = set(6, A);
    cycleCount += 8;
}

/* SET 7, B */
void Z80::Opc_cbxx_f8()
{
    B = set(7, B);
    cycleCount += 8;
}

/* SET 7, C */
void Z80::Opc_cbxx_f9()
{
    C = set(7, C);
    cycleCount += 8;
}

/* SET 7, D */
void Z80::Opc_cbxx_fa()
{
    D = set(7, D);
    cycleCount += 8;
}

/* SET 7, E */
void Z80::Opc_cbxx_fb()
{
    E = set(7, E);
    cycleCount += 8;
}

/* SET 7, H */
void Z80::Opc_cbxx_fc()
{
    H = set(7, H);
    cycleCount += 8;
}

/* SET 7, L */
void Z80::Opc_cbxx_fd()
{
    L = set(7, L);
    cycleCount += 8;
}

/* SET 7, (HL) */
void Z80::Opc_cbxx_fe()
{
    setHLi(set(7, getHLi()));
    cycleCount += 15;
}

/* SET 7, A */
void Z80::Opc_cbxx_ff()
{
    A = set(7, A);
    cycleCount += 8;
}

Z80::Opc_handler Z80::Opc_cbxx[256] =
{
    &Z80::Opc_cbxx_00,
    &Z80::Opc_cbxx_01,
    &Z80::Opc_cbxx_02,
    &Z80::Opc_cbxx_03,
    &Z80::Opc_cbxx_04,
    &Z80::Opc_cbxx_05,
    &Z80::Opc_cbxx_06,
    &Z80::Opc_cbxx_07,
    &Z80::Opc_cbxx_08,
    &Z80::Opc_cbxx_09,
    &Z80::Opc_cbxx_0a,
    &Z80::Opc_cbxx_0b,
    &Z80::Opc_cbxx_0c,
    &Z80::Opc_cbxx_0d,
    &Z80::Opc_cbxx_0e,
    &Z80::Opc_cbxx_0f,
    &Z80::Opc_cbxx_10,
    &Z80::Opc_cbxx_11,
    &Z80::Opc_cbxx_12,
    &Z80::Opc_cbxx_13,
    &Z80::Opc_cbxx_14,
    &Z80::Opc_cbxx_15,
    &Z80::Opc_cbxx_16,
    &Z80::Opc_cbxx_17,
    &Z80::Opc_cbxx_18,
    &Z80::Opc_cbxx_19,
    &Z80::Opc_cbxx_1a,
    &Z80::Opc_cbxx_1b,
    &Z80::Opc_cbxx_1c,
    &Z80::Opc_cbxx_1d,
    &Z80::Opc_cbxx_1e,
    &Z80::Opc_cbxx_1f,
    &Z80::Opc_cbxx_20,
    &Z80::Opc_cbxx_21,
    &Z80::Opc_cbxx_22,
    &Z80::Opc_cbxx_23,
    &Z80::Opc_cbxx_24,
    &Z80::Opc_cbxx_25,
    &Z80::Opc_cbxx_26,
    &Z80::Opc_cbxx_27,
    &Z80::Opc_cbxx_28,
    &Z80::Opc_cbxx_29,
    &Z80::Opc_cbxx_2a,
    &Z80::Opc_cbxx_2b,
    &Z80::Opc_cbxx_2c,
    &Z80::Opc_cbxx_2d,
    &Z80::Opc_cbxx_2e,
    &Z80::Opc_cbxx_2f,
    &Z80::Opc_cbxx_30,
    &Z80::Opc_cbxx_31,
    &Z80::Opc_cbxx_32,
    &Z80::Opc_cbxx_33,
    &Z80::Opc_cbxx_34,
    &Z80::Opc_cbxx_35,
    &Z80::Opc_cbxx_36,
    &Z80::Opc_cbxx_37,
    &Z80::Opc_cbxx_38,
    &Z80::Opc_cbxx_39,
    &Z80::Opc_cbxx_3a,
    &Z80::Opc_cbxx_3b,
    &Z80::Opc_cbxx_3c,
    &Z80::Opc_cbxx_3d,
    &Z80::Opc_cbxx_3e,
    &Z80::Opc_cbxx_3f,
    &Z80::Opc_cbxx_40,
    &Z80::Opc_cbxx_41,
    &Z80::Opc_cbxx_42,
    &Z80::Opc_cbxx_43,
    &Z80::Opc_cbxx_44,
    &Z80::Opc_cbxx_45,
    &Z80::Opc_cbxx_46,
    &Z80::Opc_cbxx_47,
    &Z80::Opc_cbxx_48,
    &Z80::Opc_cbxx_49,
    &Z80::Opc_cbxx_4a,
    &Z80::Opc_cbxx_4b,
    &Z80::Opc_cbxx_4c,
    &Z80::Opc_cbxx_4d,
    &Z80::Opc_cbxx_4e,
    &Z80::Opc_cbxx_4f,
    &Z80::Opc_cbxx_50,
    &Z80::Opc_cbxx_51,
    &Z80::Opc_cbxx_52,
    &Z80::Opc_cbxx_53,
    &Z80::Opc_cbxx_54,
    &Z80::Opc_cbxx_55,
    &Z80::Opc_cbxx_56,
    &Z80::Opc_cbxx_57,
    &Z80::Opc_cbxx_58,
    &Z80::Opc_cbxx_59,
    &Z80::Opc_cbxx_5a,
    &Z80::Opc_cbxx_5b,
    &Z80::Opc_cbxx_5c,
    &Z80::Opc_cbxx_5d,
    &Z80::Opc_cbxx_5e,
    &Z80::Opc_cbxx_5f,
    &Z80::Opc_cbxx_60,
    &Z80::Opc_cbxx_61,
    &Z80::Opc_cbxx_62,
    &Z80::Opc_cbxx_63,
    &Z80::Opc_cbxx_64,
    &Z80::Opc_cbxx_65,
    &Z80::Opc_cbxx_66,
    &Z80::Opc_cbxx_67,
    &Z80::Opc_cbxx_68,
    &Z80::Opc_cbxx_69,
    &Z80::Opc_cbxx_6a,
    &Z80::Opc_cbxx_6b,
    &Z80::Opc_cbxx_6c,
    &Z80::Opc_cbxx_6d,
    &Z80::Opc_cbxx_6e,
    &Z80::Opc_cbxx_6f,
    &Z80::Opc_cbxx_70,
    &Z80::Opc_cbxx_71,
    &Z80::Opc_cbxx_72,
    &Z80::Opc_cbxx_73,
    &Z80::Opc_cbxx_74,
    &Z80::Opc_cbxx_75,
    &Z80::Opc_cbxx_76,
    &Z80::Opc_cbxx_77,
    &Z80::Opc_cbxx_78,
    &Z80::Opc_cbxx_79,
    &Z80::Opc_cbxx_7a,
    &Z80::Opc_cbxx_7b,
    &Z80::Opc_cbxx_7c,
    &Z80::Opc_cbxx_7d,
    &Z80::Opc_cbxx_7e,
    &Z80::Opc_cbxx_7f,
    &Z80::Opc_cbxx_80,
    &Z80::Opc_cbxx_81,
    &Z80::Opc_cbxx_82,
    &Z80::Opc_cbxx_83,
    &Z80::Opc_cbxx_84,
    &Z80::Opc_cbxx_85,
    &Z80::Opc_cbxx_86,
    &Z80::Opc_cbxx_87,
    &Z80::Opc_cbxx_88,
    &Z80::Opc_cbxx_89,
    &Z80::Opc_cbxx_8a,
    &Z80::Opc_cbxx_8b,
    &Z80::Opc_cbxx_8c,
    &Z80::Opc_cbxx_8d,
    &Z80::Opc_cbxx_8e,
    &Z80::Opc_cbxx_8f,
    &Z80::Opc_cbxx_90,
    &Z80::Opc_cbxx_91,
    &Z80::Opc_cbxx_92,
    &Z80::Opc_cbxx_93,
    &Z80::Opc_cbxx_94,
    &Z80::Opc_cbxx_95,
    &Z80::Opc_cbxx_96,
    &Z80::Opc_cbxx_97,
    &Z80::Opc_cbxx_98,
    &Z80::Opc_cbxx_99,
    &Z80::Opc_cbxx_9a,
    &Z80::Opc_cbxx_9b,
    &Z80::Opc_cbxx_9c,
    &Z80::Opc_cbxx_9d,
    &Z80::Opc_cbxx_9e,
    &Z80::Opc_cbxx_9f,
    &Z80::Opc_cbxx_a0,
    &Z80::Opc_cbxx_a1,
    &Z80::Opc_cbxx_a2,
    &Z80::Opc_cbxx_a3,
    &Z80::Opc_cbxx_a4,
    &Z80::Opc_cbxx_a5,
    &Z80::Opc_cbxx_a6,
    &Z80::Opc_cbxx_a7,
    &Z80::Opc_cbxx_a8,
    &Z80::Opc_cbxx_a9,
    &Z80::Opc_cbxx_aa,
    &Z80::Opc_cbxx_ab,
    &Z80::Opc_cbxx_ac,
    &Z80::Opc_cbxx_ad,
    &Z80::Opc_cbxx_ae,
    &Z80::Opc_cbxx_af,
    &Z80::Opc_cbxx_b0,
    &Z80::Opc_cbxx_b1,
    &Z80::Opc_cbxx_b2,
    &Z80::Opc_cbxx_b3,
    &Z80::Opc_cbxx_b4,
    &Z80::Opc_cbxx_b5,
    &Z80::Opc_cbxx_b6,
    &Z80::Opc_cbxx_b7,
    &Z80::Opc_cbxx_b8,
    &Z80::Opc_cbxx_b9,
    &Z80::Opc_cbxx_ba,
    &Z80::Opc_cbxx_bb,
    &Z80::Opc_cbxx_bc,
    &Z80::Opc_cbxx_bd,
    &Z80::Opc_cbxx_be,
    &Z80::Opc_cbxx_bf,
    &Z80::Opc_cbxx_c0,
    &Z80::Opc_cbxx_c1,
    &Z80::Opc_cbxx_c2,
    &Z80::Opc_cbxx_c3,
    &Z80::Opc_cbxx_c4,
    &Z80::Opc_cbxx_c5,
    &Z80::Opc_cbxx_c6,
    &Z80::Opc_cbxx_c7,
    &Z80::Opc_cbxx_c8,
    &Z80::Opc_cbxx_c9,
    &Z80::Opc_cbxx_ca,
    &Z80::Opc_cbxx_cb,
    &Z80::Opc_cbxx_cc,
    &Z80::Opc_cbxx_cd,
    &Z80::Opc_cbxx_ce,
    &Z80::Opc_cbxx_cf,
    &Z80::Opc_cbxx_d0,
    &Z80::Opc_cbxx_d1,
    &Z80::Opc_cbxx_d2,
    &Z80::Opc_cbxx_d3,
    &Z80::Opc_cbxx_d4,
    &Z80::Opc_cbxx_d5,
    &Z80::Opc_cbxx_d6,
    &Z80::Opc_cbxx_d7,
    &Z80::Opc_cbxx_d8,
    &Z80::Opc_cbxx_d9,
    &Z80::Opc_cbxx_da,
    &Z80::Opc_cbxx_db,
    &Z80::Opc_cbxx_dc,
    &Z80::Opc_cbxx_dd,
    &Z80::Opc_cbxx_de,
    &Z80::Opc_cbxx_df,
    &Z80::Opc_cbxx_e0,
    &Z80::Opc_cbxx_e1,
    &Z80::Opc_cbxx_e2,
    &Z80::Opc_cbxx_e3,
    &Z80::Opc_cbxx_e4,
    &Z80::Opc_cbxx_e5,
    &Z80::Opc_cbxx_e6,
    &Z80::Opc_cbxx_e7,
    &Z80::Opc_cbxx_e8,
    &Z80::Opc_cbxx_e9,
    &Z80::Opc_cbxx_ea,
    &Z80::Opc_cbxx_eb,
    &Z80::Opc_cbxx_ec,
    &Z80::Opc_cbxx_ed,
    &Z80::Opc_cbxx_ee,
    &Z80::Opc_cbxx_ef,
    &Z80::Opc_cbxx_f0,
    &Z80::Opc_cbxx_f1,
    &Z80::Opc_cbxx_f2,
    &Z80::Opc_cbxx_f3,
    &Z80::Opc_cbxx_f4,
    &Z80::Opc_cbxx_f5,
    &Z80::Opc_cbxx_f6,
    &Z80::Opc_cbxx_f7,
    &Z80::Opc_cbxx_f8,
    &Z80::Opc_cbxx_f9,
    &Z80::Opc_cbxx_fa,
    &Z80::Opc_cbxx_fb,
    &Z80::Opc_cbxx_fc,
    &Z80::Opc_cbxx_fd,
    &Z80::Opc_cbxx_fe,
    &Z80::Opc_cbxx_ff
};
