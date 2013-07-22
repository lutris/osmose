/*****************************************************************************
 *
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
 * File: Opc_fdcb.cpp
 *
 * Project: Osmose emulator.
 *
 * Description: This class implements all opcodes with 0xfdcb prefixes.
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

void Z80::exec_fdcb()
{
    u8 instruction;
    R++; // Prefixed instruction increments R by one.
    IYd = (u16)(IY + (s8)env.rd8(PC++));
    instruction = env.rd8( PC++ );
    (this->*(Opc_fdcb[instruction]))();
#ifdef OPCODES_STATS
    FDCB_Prefix[ instruction ]++;
#endif
}

/* LD B, RLC (IY+d) */
void Z80::Opc_fdcb_00()
{
    B = rlc8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, RLC (IY+d) */
void Z80::Opc_fdcb_01()
{
    C = rlc8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, RLC (IY+d) */
void Z80::Opc_fdcb_02()
{
    D = rlc8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, RLC (IY+d) */
void Z80::Opc_fdcb_03()
{
    E = rlc8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, RLC (IY+d) */
void Z80::Opc_fdcb_04()
{
    H = rlc8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, RLC (IY+d) */
void Z80::Opc_fdcb_05()
{
    L = rlc8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* RLC (IY+d) */
void Z80::Opc_fdcb_06()
{
    env.wr8(IYd, rlc8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RLC (IY+d) */
void Z80::Opc_fdcb_07()
{
    A = rlc8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, RRC (IY+d) */
void Z80::Opc_fdcb_08()
{
    B = rrc8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, RRC (IY+d) */
void Z80::Opc_fdcb_09()
{
    C = rrc8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, RRC (IY+d) */
void Z80::Opc_fdcb_0a()
{
    D = rrc8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, RRC (IY+d) */
void Z80::Opc_fdcb_0b()
{
    E = rrc8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, RRC (IY+d) */
void Z80::Opc_fdcb_0c()
{
    H = rrc8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, RRC (IY+d) */
void Z80::Opc_fdcb_0d()
{
    L = rrc8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* RRC (IY+d) */
void Z80::Opc_fdcb_0e()
{
    env.wr8(IYd, rrc8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RRC (IY+d) */
void Z80::Opc_fdcb_0f()
{
    A = rrc8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, RL (IY+d) */
void Z80::Opc_fdcb_10()
{
    B = rl8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, RL (IY+d) */
void Z80::Opc_fdcb_11()
{
    C = rl8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, RL (IY+d) */
void Z80::Opc_fdcb_12()
{
    D = rl8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, RL (IY+d) */
void Z80::Opc_fdcb_13()
{
    E = rl8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, RL (IY+d) */
void Z80::Opc_fdcb_14()
{
    H = rl8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, RL (IY+d) */
void Z80::Opc_fdcb_15()
{
    L = rl8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* RL (IY+d) */
void Z80::Opc_fdcb_16()
{
    env.wr8(IYd, rl8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RL (IY+d) */
void Z80::Opc_fdcb_17()
{
    A = rl8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, RR (IY+d) */
void Z80::Opc_fdcb_18()
{
    B = rr8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, RR (IY+d) */
void Z80::Opc_fdcb_19()
{
    C = rr8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, RR (IY+d) */
void Z80::Opc_fdcb_1a()
{
    D = rr8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, RR (IY+d) */
void Z80::Opc_fdcb_1b()
{
    E = rr8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, RR (IY+d) */
void Z80::Opc_fdcb_1c()
{
    H = rr8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, RR (IY+d) */
void Z80::Opc_fdcb_1d()
{
    L = rr8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* RR (IY+d) */
void Z80::Opc_fdcb_1e()
{
    env.wr8(IYd, rr8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RR (IY+d) */
void Z80::Opc_fdcb_1f()
{
    A = rr8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, SLA (IY+d) */
void Z80::Opc_fdcb_20()
{
    B = sla8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, SLA (IY+d) */
void Z80::Opc_fdcb_21()
{
    C = sla8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, SLA (IY+d) */
void Z80::Opc_fdcb_22()
{
    D = sla8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, SLA (IY+d) */
void Z80::Opc_fdcb_23()
{
    E = sla8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, SLA (IY+d) */
void Z80::Opc_fdcb_24()
{
    H = sla8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, SLA (IY+d) */
void Z80::Opc_fdcb_25()
{
    L = sla8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* SLA (IY+d) */
void Z80::Opc_fdcb_26()
{
    env.wr8(IYd, sla8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SLA (IY+d) */
void Z80::Opc_fdcb_27()
{
    A = sla8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, SRA (IY+d) */
void Z80::Opc_fdcb_28()
{
    B = sra8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, SRA (IY+d) */
void Z80::Opc_fdcb_29()
{
    C = sra8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, SRA (IY+d) */
void Z80::Opc_fdcb_2a()
{
    D = sra8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, SRA (IY+d) */
void Z80::Opc_fdcb_2b()
{
    E = sra8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, SRA (IY+d) */
void Z80::Opc_fdcb_2c()
{
    H = sra8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, SRA (IY+d) */
void Z80::Opc_fdcb_2d()
{
    L = sra8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* SRA (IY+d) */
void Z80::Opc_fdcb_2e()
{
    env.wr8(IYd, sra8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SRA (IY+d) */
void Z80::Opc_fdcb_2f()
{
    A = sra8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, SLL (IY+d) */
void Z80::Opc_fdcb_30()
{
    B = sll8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, SLL (IY+d) */
void Z80::Opc_fdcb_31()
{
    C = sll8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, SLL (IY+d) */
void Z80::Opc_fdcb_32()
{
    D = sll8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, SLL (IY+d) */
void Z80::Opc_fdcb_33()
{
    E = sll8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, SLL (IY+d) */
void Z80::Opc_fdcb_34()
{
    H = sll8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, SLL (IY+d) */
void Z80::Opc_fdcb_35()
{
    L = sll8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* SLL (IY+d) */
void Z80::Opc_fdcb_36()
{
    env.wr8(IYd, sll8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SLL (IY+d) */
void Z80::Opc_fdcb_37()
{
    A = sll8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* LD B, SRL (IY+d) */
void Z80::Opc_fdcb_38()
{
    B = srl8(env.rd8(IYd));
    env.wr8(IYd, B);
    cycleCount += 23;
}

/* LD C, SRL (IY+d) */
void Z80::Opc_fdcb_39()
{
    C = srl8(env.rd8(IYd));
    env.wr8(IYd, C);
    cycleCount += 23;
}

/* LD D, SRL (IY+d) */
void Z80::Opc_fdcb_3a()
{
    D = srl8(env.rd8(IYd));
    env.wr8(IYd, D);
    cycleCount += 23;
}

/* LD E, SRL (IY+d) */
void Z80::Opc_fdcb_3b()
{
    E = srl8(env.rd8(IYd));
    env.wr8(IYd, E);
    cycleCount += 23;
}

/* LD H, SRL (IY+d) */
void Z80::Opc_fdcb_3c()
{
    H = srl8(env.rd8(IYd));
    env.wr8(IYd, H);
    cycleCount += 23;
}

/* LD L, SRL (IY+d) */
void Z80::Opc_fdcb_3d()
{
    L = srl8(env.rd8(IYd));
    env.wr8(IYd, L);
    cycleCount += 23;
}

/* SRL (IY+d) */
void Z80::Opc_fdcb_3e()
{
    env.wr8(IYd, srl8(env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SRL (IY+d) */
void Z80::Opc_fdcb_3f()
{
    A = srl8(env.rd8(IYd));
    env.wr8(IYd, A);
    cycleCount += 23;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_40()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_41()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_42()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_43()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_44()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_45()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_46()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 0, (IY+d) */
void Z80::Opc_fdcb_47()
{
    bit(0, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_48()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_49()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4a()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4b()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4c()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4d()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4e()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 1, (IY+d) */
void Z80::Opc_fdcb_4f()
{
    bit(1, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_50()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_51()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_52()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_53()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_54()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_55()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_56()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 2, (IY+d) */
void Z80::Opc_fdcb_57()
{
    bit(2, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_58()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_59()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5a()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5b()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5c()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5d()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5e()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 3, (IY+d) */
void Z80::Opc_fdcb_5f()
{
    bit(3, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_60()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_61()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_62()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_63()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_64()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_65()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_66()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 4, (IY+d) */
void Z80::Opc_fdcb_67()
{
    bit(4, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_68()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_69()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6a()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6b()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6c()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6d()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6e()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 5, (IY+d) */
void Z80::Opc_fdcb_6f()
{
    bit(5, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_70()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_71()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_72()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_73()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_74()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_75()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_76()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 6, (IY+d) */
void Z80::Opc_fdcb_77()
{
    bit(6, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_78()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_79()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7a()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7b()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7c()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7d()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7e()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* BIT 7, (IY+d) */
void Z80::Opc_fdcb_7f()
{
    bit(7, env.rd8(IYd));
    cycleCount += 20;
}

/* LD B, RES 0, (IY+d) */
void Z80::Opc_fdcb_80()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 0, (IY+d) */
void Z80::Opc_fdcb_81()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 0, (IY+d) */
void Z80::Opc_fdcb_82()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 0, (IY+d) */
void Z80::Opc_fdcb_83()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 0, (IY+d) */
void Z80::Opc_fdcb_84()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 0, (IY+d) */
void Z80::Opc_fdcb_85()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 0, (IY+d) */
void Z80::Opc_fdcb_86()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 0, (IY+d) */
void Z80::Opc_fdcb_87()
{
    env.wr8(IYd, res(0, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 1, (IY+d) */
void Z80::Opc_fdcb_88()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 1, (IY+d) */
void Z80::Opc_fdcb_89()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 1, (IY+d) */
void Z80::Opc_fdcb_8a()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 1, (IY+d) */
void Z80::Opc_fdcb_8b()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 1, (IY+d) */
void Z80::Opc_fdcb_8c()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 1, (IY+d) */
void Z80::Opc_fdcb_8d()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 1, (IY+d) */
void Z80::Opc_fdcb_8e()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 1, (IY+d) */
void Z80::Opc_fdcb_8f()
{
    env.wr8(IYd, res(1, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 2, (IY+d) */
void Z80::Opc_fdcb_90()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 2, (IY+d) */
void Z80::Opc_fdcb_91()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 2, (IY+d) */
void Z80::Opc_fdcb_92()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 2, (IY+d) */
void Z80::Opc_fdcb_93()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 2, (IY+d) */
void Z80::Opc_fdcb_94()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 2, (IY+d) */
void Z80::Opc_fdcb_95()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 2, (IY+d) */
void Z80::Opc_fdcb_96()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 2, (IY+d) */
void Z80::Opc_fdcb_97()
{
    env.wr8(IYd, res(2, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 3, (IY+d) */
void Z80::Opc_fdcb_98()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 3, (IY+d) */
void Z80::Opc_fdcb_99()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 3, (IY+d) */
void Z80::Opc_fdcb_9a()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 3, (IY+d) */
void Z80::Opc_fdcb_9b()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 3, (IY+d) */
void Z80::Opc_fdcb_9c()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 3, (IY+d) */
void Z80::Opc_fdcb_9d()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 3, (IY+d) */
void Z80::Opc_fdcb_9e()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 3, (IY+d) */
void Z80::Opc_fdcb_9f()
{
    env.wr8(IYd, res(3, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 4, (IY+d) */
void Z80::Opc_fdcb_a0()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 4, (IY+d) */
void Z80::Opc_fdcb_a1()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 4, (IY+d) */
void Z80::Opc_fdcb_a2()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 4, (IY+d) */
void Z80::Opc_fdcb_a3()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 4, (IY+d) */
void Z80::Opc_fdcb_a4()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 4, (IY+d) */
void Z80::Opc_fdcb_a5()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 4, (IY+d) */
void Z80::Opc_fdcb_a6()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 4, (IY+d) */
void Z80::Opc_fdcb_a7()
{
    env.wr8(IYd, res(4, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 5, (IY+d) */
void Z80::Opc_fdcb_a8()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 5, (IY+d) */
void Z80::Opc_fdcb_a9()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 5, (IY+d) */
void Z80::Opc_fdcb_aa()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 5, (IY+d) */
void Z80::Opc_fdcb_ab()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 5, (IY+d) */
void Z80::Opc_fdcb_ac()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 5, (IY+d) */
void Z80::Opc_fdcb_ad()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 5, (IY+d) */
void Z80::Opc_fdcb_ae()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 5, (IY+d) */
void Z80::Opc_fdcb_af()
{
    env.wr8(IYd, res(5, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 6, (IY+d) */
void Z80::Opc_fdcb_b0()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 6, (IY+d) */
void Z80::Opc_fdcb_b1()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 6, (IY+d) */
void Z80::Opc_fdcb_b2()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 6, (IY+d) */
void Z80::Opc_fdcb_b3()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 6, (IY+d) */
void Z80::Opc_fdcb_b4()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 6, (IY+d) */
void Z80::Opc_fdcb_b5()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* RES 6, (IY+d) */
void Z80::Opc_fdcb_b6()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 6, (IY+d) */
void Z80::Opc_fdcb_b7()
{
    env.wr8(IYd, res(6, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, RES 7, (IY+d) */
void Z80::Opc_fdcb_b8()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, RES 7, (IY+d) */
void Z80::Opc_fdcb_b9()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, RES 7, (IY+d) */
void Z80::Opc_fdcb_ba()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, RES 7, (IY+d) */
void Z80::Opc_fdcb_bb()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, RES 7, (IY+d) */
void Z80::Opc_fdcb_bc()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, RES 7, (IY+d) */
void Z80::Opc_fdcb_bd()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}


/* RES 7, (IY+d) */
void Z80::Opc_fdcb_be()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, RES 7, (IY+d) */
void Z80::Opc_fdcb_bf()
{
    env.wr8(IYd, res(7, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 0, (IY+d) */
void Z80::Opc_fdcb_c0()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 0, (IY+d) */
void Z80::Opc_fdcb_c1()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 0, (IY+d) */
void Z80::Opc_fdcb_c2()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 0, (IY+d) */
void Z80::Opc_fdcb_c3()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 0, (IY+d) */
void Z80::Opc_fdcb_c4()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 0, (IY+d) */
void Z80::Opc_fdcb_c5()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 0, (IY+d) */
void Z80::Opc_fdcb_c6()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 0, (IY+d) */
void Z80::Opc_fdcb_c7()
{
    env.wr8(IYd, set(0, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 1, (IY+d) */
void Z80::Opc_fdcb_c8()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 1, (IY+d) */
void Z80::Opc_fdcb_c9()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 1, (IY+d) */
void Z80::Opc_fdcb_ca()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 1, (IY+d) */
void Z80::Opc_fdcb_cb()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 1, (IY+d) */
void Z80::Opc_fdcb_cc()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 1, (IY+d) */
void Z80::Opc_fdcb_cd()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 1, (IY+d) */
void Z80::Opc_fdcb_ce()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 1, (IY+d) */
void Z80::Opc_fdcb_cf()
{
    env.wr8(IYd, set(1, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 2, (IY+d) */
void Z80::Opc_fdcb_d0()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 2, (IY+d) */
void Z80::Opc_fdcb_d1()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 2, (IY+d) */
void Z80::Opc_fdcb_d2()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 2, (IY+d) */
void Z80::Opc_fdcb_d3()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 2, (IY+d) */
void Z80::Opc_fdcb_d4()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 2, (IY+d) */
void Z80::Opc_fdcb_d5()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 2, (IY+d) */
void Z80::Opc_fdcb_d6()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 2, (IY+d) */
void Z80::Opc_fdcb_d7()
{
    env.wr8(IYd, set(2, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 3, (IY+d) */
void Z80::Opc_fdcb_d8()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 3, (IY+d) */
void Z80::Opc_fdcb_d9()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 3, (IY+d) */
void Z80::Opc_fdcb_da()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 3, (IY+d) */
void Z80::Opc_fdcb_db()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 3, (IY+d) */
void Z80::Opc_fdcb_dc()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 3, (IY+d) */
void Z80::Opc_fdcb_dd()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 3, (IY+d) */
void Z80::Opc_fdcb_de()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 3, (IY+d) */
void Z80::Opc_fdcb_df()
{
    env.wr8(IYd, set(3, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 4, (IY+d) */
void Z80::Opc_fdcb_e0()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 4, (IY+d) */
void Z80::Opc_fdcb_e1()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 4, (IY+d) */
void Z80::Opc_fdcb_e2()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 4, (IY+d) */
void Z80::Opc_fdcb_e3()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 4, (IY+d) */
void Z80::Opc_fdcb_e4()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 4, (IY+d) */
void Z80::Opc_fdcb_e5()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 4, (IY+d) */
void Z80::Opc_fdcb_e6()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 4, (IY+d) */
void Z80::Opc_fdcb_e7()
{
    env.wr8(IYd, set(4, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 5, (IY+d) */
void Z80::Opc_fdcb_e8()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 5, (IY+d) */
void Z80::Opc_fdcb_e9()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 5, (IY+d) */
void Z80::Opc_fdcb_ea()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 5, (IY+d) */
void Z80::Opc_fdcb_eb()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 5, (IY+d) */
void Z80::Opc_fdcb_ec()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 5, (IY+d) */
void Z80::Opc_fdcb_ed()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 5, (IY+d) */
void Z80::Opc_fdcb_ee()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 5, (IY+d) */
void Z80::Opc_fdcb_ef()
{
    env.wr8(IYd, set(5, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 6, (IY+d) */
void Z80::Opc_fdcb_f0()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 6, (IY+d) */
void Z80::Opc_fdcb_f1()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 6, (IY+d) */
void Z80::Opc_fdcb_f2()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 6, (IY+d) */
void Z80::Opc_fdcb_f3()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 6, (IY+d) */
void Z80::Opc_fdcb_f4()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 6, (IY+d) */
void Z80::Opc_fdcb_f5()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 6, (IY+d) */
void Z80::Opc_fdcb_f6()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 6, (IY+d) */
void Z80::Opc_fdcb_f7()
{
    env.wr8(IYd, set(6, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

/* LD B, SET 7, (IY+d) */
void Z80::Opc_fdcb_f8()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    B = env.rd8(IYd);
    cycleCount += 23;
}

/* LD C, SET 7, (IY+d) */
void Z80::Opc_fdcb_f9()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    C = env.rd8(IYd);
    cycleCount += 23;
}

/* LD D, SET 7, (IY+d) */
void Z80::Opc_fdcb_fa()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    D = env.rd8(IYd);
    cycleCount += 23;
}

/* LD E, SET 7, (IY+d) */
void Z80::Opc_fdcb_fb()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    E = env.rd8(IYd);
    cycleCount += 23;
}

/* LD H, SET 7, (IY+d) */
void Z80::Opc_fdcb_fc()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    H = env.rd8(IYd);
    cycleCount += 23;
}

/* LD L, SET 7, (IY+d) */
void Z80::Opc_fdcb_fd()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    L = env.rd8(IYd);
    cycleCount += 23;
}

/* SET 7, (IY+d) */
void Z80::Opc_fdcb_fe()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    cycleCount += 23;
}

/* LD A, SET 7, (IY+d) */
void Z80::Opc_fdcb_ff()
{
    env.wr8(IYd, set(7, env.rd8(IYd)));
    A = env.rd8(IYd);
    cycleCount += 23;
}

Z80::Opc_handler Z80::Opc_fdcb[256] =
{
    &Z80::Opc_fdcb_00,
    &Z80::Opc_fdcb_01,
    &Z80::Opc_fdcb_02,
    &Z80::Opc_fdcb_03,
    &Z80::Opc_fdcb_04,
    &Z80::Opc_fdcb_05,
    &Z80::Opc_fdcb_06,
    &Z80::Opc_fdcb_07,
    &Z80::Opc_fdcb_08,
    &Z80::Opc_fdcb_09,
    &Z80::Opc_fdcb_0a,
    &Z80::Opc_fdcb_0b,
    &Z80::Opc_fdcb_0c,
    &Z80::Opc_fdcb_0d,
    &Z80::Opc_fdcb_0e,
    &Z80::Opc_fdcb_0f,
    &Z80::Opc_fdcb_10,
    &Z80::Opc_fdcb_11,
    &Z80::Opc_fdcb_12,
    &Z80::Opc_fdcb_13,
    &Z80::Opc_fdcb_14,
    &Z80::Opc_fdcb_15,
    &Z80::Opc_fdcb_16,
    &Z80::Opc_fdcb_17,
    &Z80::Opc_fdcb_18,
    &Z80::Opc_fdcb_19,
    &Z80::Opc_fdcb_1a,
    &Z80::Opc_fdcb_1b,
    &Z80::Opc_fdcb_1c,
    &Z80::Opc_fdcb_1d,
    &Z80::Opc_fdcb_1e,
    &Z80::Opc_fdcb_1f,
    &Z80::Opc_fdcb_20,
    &Z80::Opc_fdcb_21,
    &Z80::Opc_fdcb_22,
    &Z80::Opc_fdcb_23,
    &Z80::Opc_fdcb_24,
    &Z80::Opc_fdcb_25,
    &Z80::Opc_fdcb_26,
    &Z80::Opc_fdcb_27,
    &Z80::Opc_fdcb_28,
    &Z80::Opc_fdcb_29,
    &Z80::Opc_fdcb_2a,
    &Z80::Opc_fdcb_2b,
    &Z80::Opc_fdcb_2c,
    &Z80::Opc_fdcb_2d,
    &Z80::Opc_fdcb_2e,
    &Z80::Opc_fdcb_2f,
    &Z80::Opc_fdcb_30,
    &Z80::Opc_fdcb_31,
    &Z80::Opc_fdcb_32,
    &Z80::Opc_fdcb_33,
    &Z80::Opc_fdcb_34,
    &Z80::Opc_fdcb_35,
    &Z80::Opc_fdcb_36,
    &Z80::Opc_fdcb_37,
    &Z80::Opc_fdcb_38,
    &Z80::Opc_fdcb_39,
    &Z80::Opc_fdcb_3a,
    &Z80::Opc_fdcb_3b,
    &Z80::Opc_fdcb_3c,
    &Z80::Opc_fdcb_3d,
    &Z80::Opc_fdcb_3e,
    &Z80::Opc_fdcb_3f,
    &Z80::Opc_fdcb_40,
    &Z80::Opc_fdcb_41,
    &Z80::Opc_fdcb_42,
    &Z80::Opc_fdcb_43,
    &Z80::Opc_fdcb_44,
    &Z80::Opc_fdcb_45,
    &Z80::Opc_fdcb_46,
    &Z80::Opc_fdcb_47,
    &Z80::Opc_fdcb_48,
    &Z80::Opc_fdcb_49,
    &Z80::Opc_fdcb_4a,
    &Z80::Opc_fdcb_4b,
    &Z80::Opc_fdcb_4c,
    &Z80::Opc_fdcb_4d,
    &Z80::Opc_fdcb_4e,
    &Z80::Opc_fdcb_4f,
    &Z80::Opc_fdcb_50,
    &Z80::Opc_fdcb_51,
    &Z80::Opc_fdcb_52,
    &Z80::Opc_fdcb_53,
    &Z80::Opc_fdcb_54,
    &Z80::Opc_fdcb_55,
    &Z80::Opc_fdcb_56,
    &Z80::Opc_fdcb_57,
    &Z80::Opc_fdcb_58,
    &Z80::Opc_fdcb_59,
    &Z80::Opc_fdcb_5a,
    &Z80::Opc_fdcb_5b,
    &Z80::Opc_fdcb_5c,
    &Z80::Opc_fdcb_5d,
    &Z80::Opc_fdcb_5e,
    &Z80::Opc_fdcb_5f,
    &Z80::Opc_fdcb_60,
    &Z80::Opc_fdcb_61,
    &Z80::Opc_fdcb_62,
    &Z80::Opc_fdcb_63,
    &Z80::Opc_fdcb_64,
    &Z80::Opc_fdcb_65,
    &Z80::Opc_fdcb_66,
    &Z80::Opc_fdcb_67,
    &Z80::Opc_fdcb_68,
    &Z80::Opc_fdcb_69,
    &Z80::Opc_fdcb_6a,
    &Z80::Opc_fdcb_6b,
    &Z80::Opc_fdcb_6c,
    &Z80::Opc_fdcb_6d,
    &Z80::Opc_fdcb_6e,
    &Z80::Opc_fdcb_6f,
    &Z80::Opc_fdcb_70,
    &Z80::Opc_fdcb_71,
    &Z80::Opc_fdcb_72,
    &Z80::Opc_fdcb_73,
    &Z80::Opc_fdcb_74,
    &Z80::Opc_fdcb_75,
    &Z80::Opc_fdcb_76,
    &Z80::Opc_fdcb_77,
    &Z80::Opc_fdcb_78,
    &Z80::Opc_fdcb_79,
    &Z80::Opc_fdcb_7a,
    &Z80::Opc_fdcb_7b,
    &Z80::Opc_fdcb_7c,
    &Z80::Opc_fdcb_7d,
    &Z80::Opc_fdcb_7e,
    &Z80::Opc_fdcb_7f,
    &Z80::Opc_fdcb_80,
    &Z80::Opc_fdcb_81,
    &Z80::Opc_fdcb_82,
    &Z80::Opc_fdcb_83,
    &Z80::Opc_fdcb_84,
    &Z80::Opc_fdcb_85,
    &Z80::Opc_fdcb_86,
    &Z80::Opc_fdcb_87,
    &Z80::Opc_fdcb_88,
    &Z80::Opc_fdcb_89,
    &Z80::Opc_fdcb_8a,
    &Z80::Opc_fdcb_8b,
    &Z80::Opc_fdcb_8c,
    &Z80::Opc_fdcb_8d,
    &Z80::Opc_fdcb_8e,
    &Z80::Opc_fdcb_8f,
    &Z80::Opc_fdcb_90,
    &Z80::Opc_fdcb_91,
    &Z80::Opc_fdcb_92,
    &Z80::Opc_fdcb_93,
    &Z80::Opc_fdcb_94,
    &Z80::Opc_fdcb_95,
    &Z80::Opc_fdcb_96,
    &Z80::Opc_fdcb_97,
    &Z80::Opc_fdcb_98,
    &Z80::Opc_fdcb_99,
    &Z80::Opc_fdcb_9a,
    &Z80::Opc_fdcb_9b,
    &Z80::Opc_fdcb_9c,
    &Z80::Opc_fdcb_9d,
    &Z80::Opc_fdcb_9e,
    &Z80::Opc_fdcb_9f,
    &Z80::Opc_fdcb_a0,
    &Z80::Opc_fdcb_a1,
    &Z80::Opc_fdcb_a2,
    &Z80::Opc_fdcb_a3,
    &Z80::Opc_fdcb_a4,
    &Z80::Opc_fdcb_a5,
    &Z80::Opc_fdcb_a6,
    &Z80::Opc_fdcb_a7,
    &Z80::Opc_fdcb_a8,
    &Z80::Opc_fdcb_a9,
    &Z80::Opc_fdcb_aa,
    &Z80::Opc_fdcb_ab,
    &Z80::Opc_fdcb_ac,
    &Z80::Opc_fdcb_ad,
    &Z80::Opc_fdcb_ae,
    &Z80::Opc_fdcb_af,
    &Z80::Opc_fdcb_b0,
    &Z80::Opc_fdcb_b1,
    &Z80::Opc_fdcb_b2,
    &Z80::Opc_fdcb_b3,
    &Z80::Opc_fdcb_b4,
    &Z80::Opc_fdcb_b5,
    &Z80::Opc_fdcb_b6,
    &Z80::Opc_fdcb_b7,
    &Z80::Opc_fdcb_b8,
    &Z80::Opc_fdcb_b9,
    &Z80::Opc_fdcb_ba,
    &Z80::Opc_fdcb_bb,
    &Z80::Opc_fdcb_bc,
    &Z80::Opc_fdcb_bd,
    &Z80::Opc_fdcb_be,
    &Z80::Opc_fdcb_bf,
    &Z80::Opc_fdcb_c0,
    &Z80::Opc_fdcb_c1,
    &Z80::Opc_fdcb_c2,
    &Z80::Opc_fdcb_c3,
    &Z80::Opc_fdcb_c4,
    &Z80::Opc_fdcb_c5,
    &Z80::Opc_fdcb_c6,
    &Z80::Opc_fdcb_c7,
    &Z80::Opc_fdcb_c8,
    &Z80::Opc_fdcb_c9,
    &Z80::Opc_fdcb_ca,
    &Z80::Opc_fdcb_cb,
    &Z80::Opc_fdcb_cc,
    &Z80::Opc_fdcb_cd,
    &Z80::Opc_fdcb_ce,
    &Z80::Opc_fdcb_cf,
    &Z80::Opc_fdcb_d0,
    &Z80::Opc_fdcb_d1,
    &Z80::Opc_fdcb_d2,
    &Z80::Opc_fdcb_d3,
    &Z80::Opc_fdcb_d4,
    &Z80::Opc_fdcb_d5,
    &Z80::Opc_fdcb_d6,
    &Z80::Opc_fdcb_d7,
    &Z80::Opc_fdcb_d8,
    &Z80::Opc_fdcb_d9,
    &Z80::Opc_fdcb_da,
    &Z80::Opc_fdcb_db,
    &Z80::Opc_fdcb_dc,
    &Z80::Opc_fdcb_dd,
    &Z80::Opc_fdcb_de,
    &Z80::Opc_fdcb_df,
    &Z80::Opc_fdcb_e0,
    &Z80::Opc_fdcb_e1,
    &Z80::Opc_fdcb_e2,
    &Z80::Opc_fdcb_e3,
    &Z80::Opc_fdcb_e4,
    &Z80::Opc_fdcb_e5,
    &Z80::Opc_fdcb_e6,
    &Z80::Opc_fdcb_e7,
    &Z80::Opc_fdcb_e8,
    &Z80::Opc_fdcb_e9,
    &Z80::Opc_fdcb_ea,
    &Z80::Opc_fdcb_eb,
    &Z80::Opc_fdcb_ec,
    &Z80::Opc_fdcb_ed,
    &Z80::Opc_fdcb_ee,
    &Z80::Opc_fdcb_ef,
    &Z80::Opc_fdcb_f0,
    &Z80::Opc_fdcb_f1,
    &Z80::Opc_fdcb_f2,
    &Z80::Opc_fdcb_f3,
    &Z80::Opc_fdcb_f4,
    &Z80::Opc_fdcb_f5,
    &Z80::Opc_fdcb_f6,
    &Z80::Opc_fdcb_f7,
    &Z80::Opc_fdcb_f8,
    &Z80::Opc_fdcb_f9,
    &Z80::Opc_fdcb_fa,
    &Z80::Opc_fdcb_fb,
    &Z80::Opc_fdcb_fc,
    &Z80::Opc_fdcb_fd,
    &Z80::Opc_fdcb_fe,
    &Z80::Opc_fdcb_ff
};
