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
 * File: Opc_ddcb.cpp
 *
 * Project: Oldspark emulator.
 *
 * Description: This class implements all opcodes with 0xddcb prefixes.
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

void Z80::exec_ddcb()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    IXd = (u16)(IX + (s8)env.rd8(PC++));
    instruction = env.rd8( PC++ );
    (this->*(Opc_ddcb[instruction]))();
#ifdef OPCODES_STATS
    DDCB_Prefix[ instruction ]++;
#endif
}

/* LD B, RLC (IX+d) */
void Z80::Opc_ddcb_00()
{
    B = rlc8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, RLC (IX+d) */
void Z80::Opc_ddcb_01()
{
    C = rlc8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, RLC (IX+d) */
void Z80::Opc_ddcb_02()
{
    D = rlc8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, RLC (IX+d) */
void Z80::Opc_ddcb_03()
{
    E = rlc8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, RLC (IX+d) */
void Z80::Opc_ddcb_04()
{
    H = rlc8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, RLC (IX+d) */
void Z80::Opc_ddcb_05()
{
    L = rlc8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* RLC (IX+d) */
void Z80::Opc_ddcb_06()
{
    env.wr8(IXd, rlc8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RLC (IX+d) */
void Z80::Opc_ddcb_07()
{
    A = rlc8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, RRC (IX+d) */
void Z80::Opc_ddcb_08()
{
    B = rrc8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, RRC (IX+d) */
void Z80::Opc_ddcb_09()
{
    C = rrc8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, RRC (IX+d) */
void Z80::Opc_ddcb_0a()
{
    D = rrc8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, RRC (IX+d) */
void Z80::Opc_ddcb_0b()
{
    E = rrc8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, RRC (IX+d) */
void Z80::Opc_ddcb_0c()
{
    H = rrc8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, RRC (IX+d) */
void Z80::Opc_ddcb_0d()
{
    L = rrc8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* RRC (IX+d) */
void Z80::Opc_ddcb_0e()
{
    env.wr8(IXd, rrc8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RRC (IX+d) */
void Z80::Opc_ddcb_0f()
{
    A = rrc8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, RL (IX+d) */
void Z80::Opc_ddcb_10()
{
    B = rl8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, RL (IX+d) */
void Z80::Opc_ddcb_11()
{
    C = rl8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, RL (IX+d) */
void Z80::Opc_ddcb_12()
{
    D = rl8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, RL (IX+d) */
void Z80::Opc_ddcb_13()
{
    E = rl8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, RL (IX+d) */
void Z80::Opc_ddcb_14()
{
    H = rl8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, RL (IX+d) */
void Z80::Opc_ddcb_15()
{
    L = rl8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* RL (IX+d) */
void Z80::Opc_ddcb_16()
{
    env.wr8(IXd, rl8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RL (IX+d) */
void Z80::Opc_ddcb_17()
{
    A = rl8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, RR (IX+d) */
void Z80::Opc_ddcb_18()
{
    B = rr8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, RR (IX+d) */
void Z80::Opc_ddcb_19()
{
    C = rr8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, RR (IX+d) */
void Z80::Opc_ddcb_1a()
{
    D = rr8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, RR (IX+d) */
void Z80::Opc_ddcb_1b()
{
    E = rr8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, RR (IX+d) */
void Z80::Opc_ddcb_1c()
{
    H = rr8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, RR (IX+d) */
void Z80::Opc_ddcb_1d()
{
    L = rr8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* RR (IX+d) */
void Z80::Opc_ddcb_1e()
{
    env.wr8(IXd, rr8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RR (IX+d) */
void Z80::Opc_ddcb_1f()
{
    A = rr8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, SLA (IX+d) */
void Z80::Opc_ddcb_20()
{
    B = sla8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, SLA (IX+d) */
void Z80::Opc_ddcb_21()
{
    C = sla8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, SLA (IX+d) */
void Z80::Opc_ddcb_22()
{
    D = sla8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, SLA (IX+d) */
void Z80::Opc_ddcb_23()
{
    E = sla8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, SLA (IX+d) */
void Z80::Opc_ddcb_24()
{
    H = sla8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, SLA (IX+d) */
void Z80::Opc_ddcb_25()
{
    L = sla8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* SLA (IX+d) */
void Z80::Opc_ddcb_26()
{
    env.wr8(IXd, sla8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SLA (IX+d) */
void Z80::Opc_ddcb_27()
{
    A = sla8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, SRA (IX+d) */
void Z80::Opc_ddcb_28()
{
    B = sra8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, SRA (IX+d) */
void Z80::Opc_ddcb_29()
{
    C = sra8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, SRA (IX+d) */
void Z80::Opc_ddcb_2a()
{
    D = sra8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, SRA (IX+d) */
void Z80::Opc_ddcb_2b()
{
    E = sra8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, SRA (IX+d) */
void Z80::Opc_ddcb_2c()
{
    H = sra8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, SRA (IX+d) */
void Z80::Opc_ddcb_2d()
{
    L = sra8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* SRA (IX+d) */
void Z80::Opc_ddcb_2e()
{
    env.wr8(IXd, sra8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SRA (IX+d) */
void Z80::Opc_ddcb_2f()
{
    A = sra8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, SLL (IX+d) */
void Z80::Opc_ddcb_30()
{
    B = sll8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, SLL (IX+d) */
void Z80::Opc_ddcb_31()
{
    C = sll8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, SLL (IX+d) */
void Z80::Opc_ddcb_32()
{
    D = sll8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, SLL (IX+d) */
void Z80::Opc_ddcb_33()
{
    E = sll8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, SLL (IX+d) */
void Z80::Opc_ddcb_34()
{
    H = sll8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, SLL (IX+d) */
void Z80::Opc_ddcb_35()
{
    L = sll8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* SLL (IX+d) */
void Z80::Opc_ddcb_36()
{
    env.wr8(IXd, sll8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SLL (IX+d) */
void Z80::Opc_ddcb_37()
{
    A = sll8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* LD B, SRL (IX+d) */
void Z80::Opc_ddcb_38()
{
    B = srl8(env.rd8(IXd));
    env.wr8(IXd, B);
    cycleCount += 23;
}

/* LD C, SRL (IX+d) */
void Z80::Opc_ddcb_39()
{
    C = srl8(env.rd8(IXd));
    env.wr8(IXd, C);
    cycleCount += 23;
}

/* LD D, SRL (IX+d) */
void Z80::Opc_ddcb_3a()
{
    D = srl8(env.rd8(IXd));
    env.wr8(IXd, D);
    cycleCount += 23;
}

/* LD E, SRL (IX+d) */
void Z80::Opc_ddcb_3b()
{
    E = srl8(env.rd8(IXd));
    env.wr8(IXd, E);
    cycleCount += 23;
}

/* LD H, SRL (IX+d) */
void Z80::Opc_ddcb_3c()
{
    H = srl8(env.rd8(IXd));
    env.wr8(IXd, H);
    cycleCount += 23;
}

/* LD L, SRL (IX+d) */
void Z80::Opc_ddcb_3d()
{
    L = srl8(env.rd8(IXd));
    env.wr8(IXd, L);
    cycleCount += 23;
}

/* SRL (IX+d) */
void Z80::Opc_ddcb_3e()
{
    env.wr8(IXd, srl8(env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SRL (IX+d) */
void Z80::Opc_ddcb_3f()
{
    A = srl8(env.rd8(IXd));
    env.wr8(IXd, A);
    cycleCount += 23;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_40()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_41()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_42()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_43()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_44()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_45()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_46()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 0, (IX+d) */
void Z80::Opc_ddcb_47()
{
    bit(0, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_48()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_49()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4a()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4b()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4c()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4d()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4e()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 1, (IX+d) */
void Z80::Opc_ddcb_4f()
{
    bit(1, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_50()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_51()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_52()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_53()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_54()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_55()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_56()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 2, (IX+d) */
void Z80::Opc_ddcb_57()
{
    bit(2, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_58()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_59()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5a()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5b()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5c()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5d()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5e()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 3, (IX+d) */
void Z80::Opc_ddcb_5f()
{
    bit(3, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_60()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_61()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_62()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_63()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_64()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_65()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_66()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 4, (IX+d) */
void Z80::Opc_ddcb_67()
{
    bit(4, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_68()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_69()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6a()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6b()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6c()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6d()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6e()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 5, (IX+d) */
void Z80::Opc_ddcb_6f()
{
    bit(5, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_70()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_71()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_72()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_73()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_74()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_75()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_76()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 6, (IX+d) */
void Z80::Opc_ddcb_77()
{
    bit(6, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_78()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_79()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7a()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7b()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7c()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7d()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7e()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* BIT 7, (IX+d) */
void Z80::Opc_ddcb_7f()
{
    bit(7, env.rd8(IXd));
    cycleCount += 20;
}

/* LD B, RES 0, (IX+d) */
void Z80::Opc_ddcb_80()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 0, (IX+d) */
void Z80::Opc_ddcb_81()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 0, (IX+d) */
void Z80::Opc_ddcb_82()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 0, (IX+d) */
void Z80::Opc_ddcb_83()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 0, (IX+d) */
void Z80::Opc_ddcb_84()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 0, (IX+d) */
void Z80::Opc_ddcb_85()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 0, (IX+d) */
void Z80::Opc_ddcb_86()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 0, (IX+d) */
void Z80::Opc_ddcb_87()
{
    env.wr8(IXd, res(0, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 1, (IX+d) */
void Z80::Opc_ddcb_88()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 1, (IX+d) */
void Z80::Opc_ddcb_89()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 1, (IX+d) */
void Z80::Opc_ddcb_8a()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 1, (IX+d) */
void Z80::Opc_ddcb_8b()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 1, (IX+d) */
void Z80::Opc_ddcb_8c()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 1, (IX+d) */
void Z80::Opc_ddcb_8d()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 1, (IX+d) */
void Z80::Opc_ddcb_8e()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 1, (IX+d) */
void Z80::Opc_ddcb_8f()
{
    env.wr8(IXd, res(1, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 2, (IX+d) */
void Z80::Opc_ddcb_90()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 2, (IX+d) */
void Z80::Opc_ddcb_91()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 2, (IX+d) */
void Z80::Opc_ddcb_92()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 2, (IX+d) */
void Z80::Opc_ddcb_93()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 2, (IX+d) */
void Z80::Opc_ddcb_94()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 2, (IX+d) */
void Z80::Opc_ddcb_95()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 2, (IX+d) */
void Z80::Opc_ddcb_96()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 2, (IX+d) */
void Z80::Opc_ddcb_97()
{
    env.wr8(IXd, res(2, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 3, (IX+d) */
void Z80::Opc_ddcb_98()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 3, (IX+d) */
void Z80::Opc_ddcb_99()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 3, (IX+d) */
void Z80::Opc_ddcb_9a()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 3, (IX+d) */
void Z80::Opc_ddcb_9b()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 3, (IX+d) */
void Z80::Opc_ddcb_9c()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 3, (IX+d) */
void Z80::Opc_ddcb_9d()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 3, (IX+d) */
void Z80::Opc_ddcb_9e()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 3, (IX+d) */
void Z80::Opc_ddcb_9f()
{
    env.wr8(IXd, res(3, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 4, (IX+d) */
void Z80::Opc_ddcb_a0()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 4, (IX+d) */
void Z80::Opc_ddcb_a1()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 4, (IX+d) */
void Z80::Opc_ddcb_a2()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 4, (IX+d) */
void Z80::Opc_ddcb_a3()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 4, (IX+d) */
void Z80::Opc_ddcb_a4()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 4, (IX+d) */
void Z80::Opc_ddcb_a5()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 4, (IX+d) */
void Z80::Opc_ddcb_a6()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 4, (IX+d) */
void Z80::Opc_ddcb_a7()
{
    env.wr8(IXd, res(4, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 5, (IX+d) */
void Z80::Opc_ddcb_a8()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 5, (IX+d) */
void Z80::Opc_ddcb_a9()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 5, (IX+d) */
void Z80::Opc_ddcb_aa()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 5, (IX+d) */
void Z80::Opc_ddcb_ab()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 5, (IX+d) */
void Z80::Opc_ddcb_ac()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 5, (IX+d) */
void Z80::Opc_ddcb_ad()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 5, (IX+d) */
void Z80::Opc_ddcb_ae()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 5, (IX+d) */
void Z80::Opc_ddcb_af()
{
    env.wr8(IXd, res(5, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 6, (IX+d) */
void Z80::Opc_ddcb_b0()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 6, (IX+d) */
void Z80::Opc_ddcb_b1()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 6, (IX+d) */
void Z80::Opc_ddcb_b2()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 6, (IX+d) */
void Z80::Opc_ddcb_b3()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 6, (IX+d) */
void Z80::Opc_ddcb_b4()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 6, (IX+d) */
void Z80::Opc_ddcb_b5()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* RES 6, (IX+d) */
void Z80::Opc_ddcb_b6()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 6, (IX+d) */
void Z80::Opc_ddcb_b7()
{
    env.wr8(IXd, res(6, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, RES 7, (IX+d) */
void Z80::Opc_ddcb_b8()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, RES 7, (IX+d) */
void Z80::Opc_ddcb_b9()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, RES 7, (IX+d) */
void Z80::Opc_ddcb_ba()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, RES 7, (IX+d) */
void Z80::Opc_ddcb_bb()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, RES 7, (IX+d) */
void Z80::Opc_ddcb_bc()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, RES 7, (IX+d) */
void Z80::Opc_ddcb_bd()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}


/* RES 7, (IX+d) */
void Z80::Opc_ddcb_be()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, RES 7, (IX+d) */
void Z80::Opc_ddcb_bf()
{
    env.wr8(IXd, res(7, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 0, (IX+d) */
void Z80::Opc_ddcb_c0()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 0, (IX+d) */
void Z80::Opc_ddcb_c1()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 0, (IX+d) */
void Z80::Opc_ddcb_c2()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 0, (IX+d) */
void Z80::Opc_ddcb_c3()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 0, (IX+d) */
void Z80::Opc_ddcb_c4()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 0, (IX+d) */
void Z80::Opc_ddcb_c5()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 0, (IX+d) */
void Z80::Opc_ddcb_c6()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 0, (IX+d) */
void Z80::Opc_ddcb_c7()
{
    env.wr8(IXd, set(0, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 1, (IX+d) */
void Z80::Opc_ddcb_c8()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 1, (IX+d) */
void Z80::Opc_ddcb_c9()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 1, (IX+d) */
void Z80::Opc_ddcb_ca()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 1, (IX+d) */
void Z80::Opc_ddcb_cb()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 1, (IX+d) */
void Z80::Opc_ddcb_cc()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 1, (IX+d) */
void Z80::Opc_ddcb_cd()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 1, (IX+d) */
void Z80::Opc_ddcb_ce()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 1, (IX+d) */
void Z80::Opc_ddcb_cf()
{
    env.wr8(IXd, set(1, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 2, (IX+d) */
void Z80::Opc_ddcb_d0()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 2, (IX+d) */
void Z80::Opc_ddcb_d1()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 2, (IX+d) */
void Z80::Opc_ddcb_d2()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 2, (IX+d) */
void Z80::Opc_ddcb_d3()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 2, (IX+d) */
void Z80::Opc_ddcb_d4()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 2, (IX+d) */
void Z80::Opc_ddcb_d5()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 2, (IX+d) */
void Z80::Opc_ddcb_d6()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 2, (IX+d) */
void Z80::Opc_ddcb_d7()
{
    env.wr8(IXd, set(2, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 3, (IX+d) */
void Z80::Opc_ddcb_d8()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 3, (IX+d) */
void Z80::Opc_ddcb_d9()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 3, (IX+d) */
void Z80::Opc_ddcb_da()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 3, (IX+d) */
void Z80::Opc_ddcb_db()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 3, (IX+d) */
void Z80::Opc_ddcb_dc()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 3, (IX+d) */
void Z80::Opc_ddcb_dd()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 3, (IX+d) */
void Z80::Opc_ddcb_de()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 3, (IX+d) */
void Z80::Opc_ddcb_df()
{
    env.wr8(IXd, set(3, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 4, (IX+d) */
void Z80::Opc_ddcb_e0()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 4, (IX+d) */
void Z80::Opc_ddcb_e1()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 4, (IX+d) */
void Z80::Opc_ddcb_e2()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 4, (IX+d) */
void Z80::Opc_ddcb_e3()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 4, (IX+d) */
void Z80::Opc_ddcb_e4()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 4, (IX+d) */
void Z80::Opc_ddcb_e5()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 4, (IX+d) */
void Z80::Opc_ddcb_e6()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 4, (IX+d) */
void Z80::Opc_ddcb_e7()
{
    env.wr8(IXd, set(4, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 5, (IX+d) */
void Z80::Opc_ddcb_e8()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 5, (IX+d) */
void Z80::Opc_ddcb_e9()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 5, (IX+d) */
void Z80::Opc_ddcb_ea()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 5, (IX+d) */
void Z80::Opc_ddcb_eb()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 5, (IX+d) */
void Z80::Opc_ddcb_ec()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 5, (IX+d) */
void Z80::Opc_ddcb_ed()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 5, (IX+d) */
void Z80::Opc_ddcb_ee()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 5, (IX+d) */
void Z80::Opc_ddcb_ef()
{
    env.wr8(IXd, set(5, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 6, (IX+d) */
void Z80::Opc_ddcb_f0()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 6, (IX+d) */
void Z80::Opc_ddcb_f1()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 6, (IX+d) */
void Z80::Opc_ddcb_f2()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 6, (IX+d) */
void Z80::Opc_ddcb_f3()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 6, (IX+d) */
void Z80::Opc_ddcb_f4()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 6, (IX+d) */
void Z80::Opc_ddcb_f5()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 6, (IX+d) */
void Z80::Opc_ddcb_f6()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 6, (IX+d) */
void Z80::Opc_ddcb_f7()
{
    env.wr8(IXd, set(6, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}

/* LD B, SET 7, (IX+d) */
void Z80::Opc_ddcb_f8()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    B = env.rd8(IXd);
    cycleCount += 23;
}

/* LD C, SET 7, (IX+d) */
void Z80::Opc_ddcb_f9()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    C = env.rd8(IXd);
    cycleCount += 23;
}

/* LD D, SET 7, (IX+d) */
void Z80::Opc_ddcb_fa()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    D = env.rd8(IXd);
    cycleCount += 23;
}

/* LD E, SET 7, (IX+d) */
void Z80::Opc_ddcb_fb()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    E = env.rd8(IXd);
    cycleCount += 23;
}

/* LD H, SET 7, (IX+d) */
void Z80::Opc_ddcb_fc()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    H = env.rd8(IXd);
    cycleCount += 23;
}

/* LD L, SET 7, (IX+d) */
void Z80::Opc_ddcb_fd()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    L = env.rd8(IXd);
    cycleCount += 23;
}

/* SET 7, (IX+d) */
void Z80::Opc_ddcb_fe()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    cycleCount += 23;
}

/* LD A, SET 7, (IX+d) */
void Z80::Opc_ddcb_ff()
{
    env.wr8(IXd, set(7, env.rd8(IXd)));
    A = env.rd8(IXd);
    cycleCount += 23;
}


Z80::Opc_handler Z80::Opc_ddcb[256] =
{
    &Z80::Opc_ddcb_00,
    &Z80::Opc_ddcb_01,
    &Z80::Opc_ddcb_02,
    &Z80::Opc_ddcb_03,
    &Z80::Opc_ddcb_04,
    &Z80::Opc_ddcb_05,
    &Z80::Opc_ddcb_06,
    &Z80::Opc_ddcb_07,
    &Z80::Opc_ddcb_08,
    &Z80::Opc_ddcb_09,
    &Z80::Opc_ddcb_0a,
    &Z80::Opc_ddcb_0b,
    &Z80::Opc_ddcb_0c,
    &Z80::Opc_ddcb_0d,
    &Z80::Opc_ddcb_0e,
    &Z80::Opc_ddcb_0f,
    &Z80::Opc_ddcb_10,
    &Z80::Opc_ddcb_11,
    &Z80::Opc_ddcb_12,
    &Z80::Opc_ddcb_13,
    &Z80::Opc_ddcb_14,
    &Z80::Opc_ddcb_15,
    &Z80::Opc_ddcb_16,
    &Z80::Opc_ddcb_17,
    &Z80::Opc_ddcb_18,
    &Z80::Opc_ddcb_19,
    &Z80::Opc_ddcb_1a,
    &Z80::Opc_ddcb_1b,
    &Z80::Opc_ddcb_1c,
    &Z80::Opc_ddcb_1d,
    &Z80::Opc_ddcb_1e,
    &Z80::Opc_ddcb_1f,
    &Z80::Opc_ddcb_20,
    &Z80::Opc_ddcb_21,
    &Z80::Opc_ddcb_22,
    &Z80::Opc_ddcb_23,
    &Z80::Opc_ddcb_24,
    &Z80::Opc_ddcb_25,
    &Z80::Opc_ddcb_26,
    &Z80::Opc_ddcb_27,
    &Z80::Opc_ddcb_28,
    &Z80::Opc_ddcb_29,
    &Z80::Opc_ddcb_2a,
    &Z80::Opc_ddcb_2b,
    &Z80::Opc_ddcb_2c,
    &Z80::Opc_ddcb_2d,
    &Z80::Opc_ddcb_2e,
    &Z80::Opc_ddcb_2f,
    &Z80::Opc_ddcb_30,
    &Z80::Opc_ddcb_31,
    &Z80::Opc_ddcb_32,
    &Z80::Opc_ddcb_33,
    &Z80::Opc_ddcb_34,
    &Z80::Opc_ddcb_35,
    &Z80::Opc_ddcb_36,
    &Z80::Opc_ddcb_37,
    &Z80::Opc_ddcb_38,
    &Z80::Opc_ddcb_39,
    &Z80::Opc_ddcb_3a,
    &Z80::Opc_ddcb_3b,
    &Z80::Opc_ddcb_3c,
    &Z80::Opc_ddcb_3d,
    &Z80::Opc_ddcb_3e,
    &Z80::Opc_ddcb_3f,
    &Z80::Opc_ddcb_40,
    &Z80::Opc_ddcb_41,
    &Z80::Opc_ddcb_42,
    &Z80::Opc_ddcb_43,
    &Z80::Opc_ddcb_44,
    &Z80::Opc_ddcb_45,
    &Z80::Opc_ddcb_46,
    &Z80::Opc_ddcb_47,
    &Z80::Opc_ddcb_48,
    &Z80::Opc_ddcb_49,
    &Z80::Opc_ddcb_4a,
    &Z80::Opc_ddcb_4b,
    &Z80::Opc_ddcb_4c,
    &Z80::Opc_ddcb_4d,
    &Z80::Opc_ddcb_4e,
    &Z80::Opc_ddcb_4f,
    &Z80::Opc_ddcb_50,
    &Z80::Opc_ddcb_51,
    &Z80::Opc_ddcb_52,
    &Z80::Opc_ddcb_53,
    &Z80::Opc_ddcb_54,
    &Z80::Opc_ddcb_55,
    &Z80::Opc_ddcb_56,
    &Z80::Opc_ddcb_57,
    &Z80::Opc_ddcb_58,
    &Z80::Opc_ddcb_59,
    &Z80::Opc_ddcb_5a,
    &Z80::Opc_ddcb_5b,
    &Z80::Opc_ddcb_5c,
    &Z80::Opc_ddcb_5d,
    &Z80::Opc_ddcb_5e,
    &Z80::Opc_ddcb_5f,
    &Z80::Opc_ddcb_60,
    &Z80::Opc_ddcb_61,
    &Z80::Opc_ddcb_62,
    &Z80::Opc_ddcb_63,
    &Z80::Opc_ddcb_64,
    &Z80::Opc_ddcb_65,
    &Z80::Opc_ddcb_66,
    &Z80::Opc_ddcb_67,
    &Z80::Opc_ddcb_68,
    &Z80::Opc_ddcb_69,
    &Z80::Opc_ddcb_6a,
    &Z80::Opc_ddcb_6b,
    &Z80::Opc_ddcb_6c,
    &Z80::Opc_ddcb_6d,
    &Z80::Opc_ddcb_6e,
    &Z80::Opc_ddcb_6f,
    &Z80::Opc_ddcb_70,
    &Z80::Opc_ddcb_71,
    &Z80::Opc_ddcb_72,
    &Z80::Opc_ddcb_73,
    &Z80::Opc_ddcb_74,
    &Z80::Opc_ddcb_75,
    &Z80::Opc_ddcb_76,
    &Z80::Opc_ddcb_77,
    &Z80::Opc_ddcb_78,
    &Z80::Opc_ddcb_79,
    &Z80::Opc_ddcb_7a,
    &Z80::Opc_ddcb_7b,
    &Z80::Opc_ddcb_7c,
    &Z80::Opc_ddcb_7d,
    &Z80::Opc_ddcb_7e,
    &Z80::Opc_ddcb_7f,
    &Z80::Opc_ddcb_80,
    &Z80::Opc_ddcb_81,
    &Z80::Opc_ddcb_82,
    &Z80::Opc_ddcb_83,
    &Z80::Opc_ddcb_84,
    &Z80::Opc_ddcb_85,
    &Z80::Opc_ddcb_86,
    &Z80::Opc_ddcb_87,
    &Z80::Opc_ddcb_88,
    &Z80::Opc_ddcb_89,
    &Z80::Opc_ddcb_8a,
    &Z80::Opc_ddcb_8b,
    &Z80::Opc_ddcb_8c,
    &Z80::Opc_ddcb_8d,
    &Z80::Opc_ddcb_8e,
    &Z80::Opc_ddcb_8f,
    &Z80::Opc_ddcb_90,
    &Z80::Opc_ddcb_91,
    &Z80::Opc_ddcb_92,
    &Z80::Opc_ddcb_93,
    &Z80::Opc_ddcb_94,
    &Z80::Opc_ddcb_95,
    &Z80::Opc_ddcb_96,
    &Z80::Opc_ddcb_97,
    &Z80::Opc_ddcb_98,
    &Z80::Opc_ddcb_99,
    &Z80::Opc_ddcb_9a,
    &Z80::Opc_ddcb_9b,
    &Z80::Opc_ddcb_9c,
    &Z80::Opc_ddcb_9d,
    &Z80::Opc_ddcb_9e,
    &Z80::Opc_ddcb_9f,
    &Z80::Opc_ddcb_a0,
    &Z80::Opc_ddcb_a1,
    &Z80::Opc_ddcb_a2,
    &Z80::Opc_ddcb_a3,
    &Z80::Opc_ddcb_a4,
    &Z80::Opc_ddcb_a5,
    &Z80::Opc_ddcb_a6,
    &Z80::Opc_ddcb_a7,
    &Z80::Opc_ddcb_a8,
    &Z80::Opc_ddcb_a9,
    &Z80::Opc_ddcb_aa,
    &Z80::Opc_ddcb_ab,
    &Z80::Opc_ddcb_ac,
    &Z80::Opc_ddcb_ad,
    &Z80::Opc_ddcb_ae,
    &Z80::Opc_ddcb_af,
    &Z80::Opc_ddcb_b0,
    &Z80::Opc_ddcb_b1,
    &Z80::Opc_ddcb_b2,
    &Z80::Opc_ddcb_b3,
    &Z80::Opc_ddcb_b4,
    &Z80::Opc_ddcb_b5,
    &Z80::Opc_ddcb_b6,
    &Z80::Opc_ddcb_b7,
    &Z80::Opc_ddcb_b8,
    &Z80::Opc_ddcb_b9,
    &Z80::Opc_ddcb_ba,
    &Z80::Opc_ddcb_bb,
    &Z80::Opc_ddcb_bc,
    &Z80::Opc_ddcb_bd,
    &Z80::Opc_ddcb_be,
    &Z80::Opc_ddcb_bf,
    &Z80::Opc_ddcb_c0,
    &Z80::Opc_ddcb_c1,
    &Z80::Opc_ddcb_c2,
    &Z80::Opc_ddcb_c3,
    &Z80::Opc_ddcb_c4,
    &Z80::Opc_ddcb_c5,
    &Z80::Opc_ddcb_c6,
    &Z80::Opc_ddcb_c7,
    &Z80::Opc_ddcb_c8,
    &Z80::Opc_ddcb_c9,
    &Z80::Opc_ddcb_ca,
    &Z80::Opc_ddcb_cb,
    &Z80::Opc_ddcb_cc,
    &Z80::Opc_ddcb_cd,
    &Z80::Opc_ddcb_ce,
    &Z80::Opc_ddcb_cf,
    &Z80::Opc_ddcb_d0,
    &Z80::Opc_ddcb_d1,
    &Z80::Opc_ddcb_d2,
    &Z80::Opc_ddcb_d3,
    &Z80::Opc_ddcb_d4,
    &Z80::Opc_ddcb_d5,
    &Z80::Opc_ddcb_d6,
    &Z80::Opc_ddcb_d7,
    &Z80::Opc_ddcb_d8,
    &Z80::Opc_ddcb_d9,
    &Z80::Opc_ddcb_da,
    &Z80::Opc_ddcb_db,
    &Z80::Opc_ddcb_dc,
    &Z80::Opc_ddcb_dd,
    &Z80::Opc_ddcb_de,
    &Z80::Opc_ddcb_df,
    &Z80::Opc_ddcb_e0,
    &Z80::Opc_ddcb_e1,
    &Z80::Opc_ddcb_e2,
    &Z80::Opc_ddcb_e3,
    &Z80::Opc_ddcb_e4,
    &Z80::Opc_ddcb_e5,
    &Z80::Opc_ddcb_e6,
    &Z80::Opc_ddcb_e7,
    &Z80::Opc_ddcb_e8,
    &Z80::Opc_ddcb_e9,
    &Z80::Opc_ddcb_ea,
    &Z80::Opc_ddcb_eb,
    &Z80::Opc_ddcb_ec,
    &Z80::Opc_ddcb_ed,
    &Z80::Opc_ddcb_ee,
    &Z80::Opc_ddcb_ef,
    &Z80::Opc_ddcb_f0,
    &Z80::Opc_ddcb_f1,
    &Z80::Opc_ddcb_f2,
    &Z80::Opc_ddcb_f3,
    &Z80::Opc_ddcb_f4,
    &Z80::Opc_ddcb_f5,
    &Z80::Opc_ddcb_f6,
    &Z80::Opc_ddcb_f7,
    &Z80::Opc_ddcb_f8,
    &Z80::Opc_ddcb_f9,
    &Z80::Opc_ddcb_fa,
    &Z80::Opc_ddcb_fb,
    &Z80::Opc_ddcb_fc,
    &Z80::Opc_ddcb_fd,
    &Z80::Opc_ddcb_fe,
    &Z80::Opc_ddcb_ff
};
