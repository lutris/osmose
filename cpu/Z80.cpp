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
 * Description: This class implements Z80 cpu emulator. It's table driven, and all
 * opcodes are supported. Not that undocumented flags are not totaly supported.
 * In these files are defined almost all ALU, and Shift operations. Address mode
 * getters and setters are define in Z80.h as statics methods.
 *
 * Author: Vedder Bruno
 * Date: 10/01/2006, Thailand, Laos Cambodia :-)
 *
 * URL: http://bcz.asterope.fr
 *****************************************************************************/

#include "Z80.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Precomputed parity, sign and zero flags table.
u8 Z80::PF_SF_ZF_[256] =
{
    ZF|PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF,
    SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF,
    SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF,
    SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF,
    SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF,
    SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF,
    SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF,
    SF|PF, SF, SF, SF|PF, SF, SF|PF, SF|PF, SF, SF, SF|PF, SF|PF, SF, SF|PF, SF, SF, SF|PF
};

// Precomputed parity table.
u8 Z80::PF_[256] =
{
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    0, PF, PF, 0, PF, 0, 0, PF, PF, 0, 0, PF, 0, PF, PF, 0,
    PF, 0, 0, PF, 0, PF, PF, 0, 0, PF, PF, 0, PF, 0, 0, PF
};

u8 Z80::bitval[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

/* Constructor, initialise env reference. */
Z80::Z80( Z80Environment &_env ): env( _env )
{
#ifdef OPCODES_STATS
    NO_Prefix = new u32[256];
    CB_Prefix = new u32[256];
    DD_Prefix = new u32[256];
    ED_Prefix = new u32[256];
    FD_Prefix = new u32[256];
    DDCB_Prefix = new u32[256];
    FDCB_Prefix = new u32[256];

    // Clear Statistics tables.
    for ( u16 i = 0; i < 256; i++ )
    {
        NO_Prefix[i] = 0;
        CB_Prefix[i] = 0;
        DD_Prefix[i] = 0;
        ED_Prefix[i] = 0;
        FD_Prefix[i] = 0;
        DDCB_Prefix[i] = 0;
        FDCB_Prefix[i] = 0;
    }
#endif
    reset();
}

#ifdef OPCODES_STATS
void Z80::opcodes_stats()
{
    printf( "No prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0x%.2x used %d times.\n", i, NO_Prefix[i] );
    }

    printf( "\nCB prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xCB%.2x used %d times.\n", i, CB_Prefix[i] );
    }

    printf( "\nDD prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xDD%.2x used %d times.\n", i, DD_Prefix[i] );
    }

    printf( "\nDDCB prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xDDCB%.2x used %d times.\n", i, DDCB_Prefix[i] );
    }

    printf( "\nED prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xED%.2x used %d times.\n", i, ED_Prefix[i] );
    }

    printf( "\nFD prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xFD%.2x used %d times.\n", i, FD_Prefix[i] );
    }

    printf( "\nFDCB prefixed instructions\n" );
    for ( u16 i = 0; i < 256; i++ )
    {
        printf( "0xFDCB%.2x used %d times.\n", i, FDCB_Prefix[i] );
    }
}
#endif

/* Destructor */
Z80::~Z80() {}

void Z80::reset()
{
    F = ZF;
    A = B = C = D = E = H = L = I = R = Rbit7 =0x0;
    A1 = B1 = C1 = D1 = E1 = H1 = L1 = 0x0;
    IX = IY = PC = 0x0000;
    SP = 0xF000;
    IFF1 = IFF2 = cpuHalted = false; /* IRQ/HALT opcode flags */
    IM = 0;                          /* interrupt mode set to Zero. */
    cycleCount = 0;                  /* Reset CPU cycles counter.    */
}

void Z80::dump( u16 addr )
{
    printf( "%.4x : ", addr );
    for ( int i = 0; i < 8; i++ )
    {
        printf( "%.2x ", env.rd8(( addr + i ) &0xFFFF ));
    }
    printf( "\n" );
}

/**
 * Basic Arithmetic CPU Operations:
 */
u8 Z80::inc8( u8 v )
{
    v++;                        /* Inc value, wrap on 8 bits 	*/
    F &= CF;                    /* Clear all used flags 	*/
    F |= ( v &0x80 );           /* Save S flag (bit sign)	*/
    if ( v == 0 ) F |= ZF;      /* If v is zero Set Zero bit.	*/
    if ( v == 0x80 ) F |= VF;   /* Set Overflow flag		*/
    if ( !( v &0xf )) F |= 0x10; /* Half flag if Carry from bit 3*/
//    F |= ( v &( YF | XF ));     /* undocumented flag bits 5+3 */
    return ( v );
}


u8 Z80::dec8( u8 v )
{
    v--;                              /* Dec value, wrap on 8 bit	*/
    F = ( F &CF ) | NF;               /* Clear all used flags set N */
    F |= ( v &SF );                   /* Save S flag (bit sign)	*/
    if ( v == 0 ) F |= ZF;            /* If v is zero Set Zero bit.	*/
    if ( v == 0x7f ) F |= VF;         /* Set overflow flag		*/
    if (( v &0x0f ) == 0x0f ) F |= HF; /* Half carry 		*/
//    F |= ( v &( YF | XF ));           /* undocumented flag bits 5+3 */
    return ( v );
}

/* Add -> Never overflow if sign a != sign b */
/* if sign a == sign b then  (a^b)& 80 is 0 , so overflow possible */
/* ~(a^b)& 80 gives opposite result that we AND with second condition to overflow:*/
/* a & F sign != means overflow -> (a^F)&0x80 true mean overflow. */
/* Luckily sign is stored in bit 7 in F, so we xor can A and F */
u8 Z80::add8( u8 a, u8 b )
{
    u16 tmp1 = (( a + b ));
    F = ( tmp1 &0x80 );                        /* Set sign */
    F |= ( tmp1 >> 8 );                        /* Set Carry */
    tmp1 &= 0xff;                              /* 8bit wrap */
    if (( tmp1 ^ a ^ b ) &0x10 ) F |= HF;      /* Set Half flag */
    if ( ~( a ^ b ) &( a ^ F ) &0x80 ) F |= VF; /* Set VF flag  F already has sign.*/
    if ( tmp1 == 0 ) F |= ZF;                  /* Set Zero Flag */
//    F |= ( tmp1 &( YF | XF ));                 /* undocumented flag bits 5+3 */
    return tmp1;
}

u8 Z80::adc8( u8 a, u8 b )
{
    u16 tmp1 = (( a + b ) + ( F &CF ));
    F = ( tmp1 &0x80 );                          /* Save sign */
    F |= (( tmp1 ) >> 8 );                       /* Set Carry */
    tmp1 &= 0xff;                                /* 8bit wrap */
    if ( tmp1 == 0 ) F |= ZF;                    /* Set Zero Flag */
    if ((( a ^ b ^ tmp1 ) &0x10 ) != 0 ) F |= HF; /* Set Half flag */
    if ( ~( a ^ b ) &( a ^ F ) &0x80 ) F |= VF;  /* Set VF flag  F already has sign.*/
//    F |= ( tmp1 &( YF | XF ));                   /* undocumented flag bits 5+3 */
    return tmp1;
}

u8 Z80::sbc8( u8 a, u8 b )
{
    u16 tmp1 = a - b - ( F &CF );
    F = ( tmp1 &0x80 ) | NF;      /* save sign, set NF */
    F |= (( tmp1 &0x100 ) >> 8 ); /* save carry */
    if ((( a ^ b ^ tmp1 ) &0x10 ) != 0 ) F |= HF;
    if ((( b ^ a ) &( a ^ tmp1 ) &0x80 ) != 0 ) F |= VF;
    tmp1 &= 0xff;
    if ( tmp1 == 0 ) F |= ZF;
//    F |= ( tmp1 &( YF | XF ));    /* undocumented flag bits 5+3 */
    return tmp1;
}

u8 Z80::sub8( u8 a, u8 b )
{
    u16 tmp1 = ( a - b );
    F = ( tmp1 &0x80 ) | NF; /* Save sign, set N flag */
    if ( tmp1 == 0 ) F |= ZF;    /* Set Zero Flag */
    F |= ( tmp1 &0x100 ) >> 8; /* Set Carry */
    if ((( b ^ a ) &( a ^ tmp1 ) &0x80 ) != 0 ) F |= VF; /* Set overflow */
    if ((( a ^ b ^ tmp1 ) &0x10 ) != 0 ) F |= HF; /* Set Half flag */
    tmp1 &= 0xff;
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u16 Z80::add16( u16 a, u16 b )
{
    u32 res = a + b;
    F &= SF | ZF | PF;
    if ( res > 0xFFFF ) F |= CF;
    if ((( a &0xFFF ) + ( b &0xFFF )) > 0xFFF ) F |= HF;
    return ( res &0xFFFF );
}


void Z80::sbcHL( u16 value )
{
    u16 _HLD = getHL();
    u32 result = _HLD - value - ( F &1 );
    F = ((( _HLD ^ result ^ value ) >> 8 ) &0x10 ) | 0x02;
    F |= (( result >> 16 ) &1 ) | (( result >> 8 ) &0x80 );
    F |= ((( result &0xffff ) != 0 ) ? 0 : 0x40 );
    F |= ((( value ^ _HLD ) &( _HLD ^ result ) &0x8000 ) >> 13 );
    H = ( result >> 8 ) &0xff;
    L = result &0xff;
    cycleCount += 15;
}

void Z80::adcHL( u16 value )
{
    u16 tmp1 = getHL();
    u32 result = tmp1 + value + ( F &1 );
    F = ((( tmp1 ^ result ^ value ) >> 8 ) &0x10 );
    F |= (( result >> 16 ) &1 ) | (( result >> 8 ) &0x80 );
    F |= ((( result &0xffff ) != 0 ) ? 0 : 0x40 );
    F |= ((( value ^ tmp1 ^ 0x8000 ) &( value ^ result ) &0x8000 ) >> 13 );
    H = ( result >> 8 ) &0xff;
    L = result &0xff;
    cycleCount += 15;

}

/* Acts like sub, but do not affect operands.*/
void Z80::cp8( u8 a, u8 b )
{
    sub8( a, b );
}

/**
 * Basic Logical CPU Operations:
 */
u8 Z80::and8( u8 a, u8 b )
{
    u8 tmp1 = ( a & b );
    F = HF; /* Set H, clear SZ H P/V N and C */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return ( tmp1 );
}

u8 Z80::xor8( u8 a, u8 b )
{
    u8 tmp1 = ( a ^ b );
    F = PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}

u8 Z80::or8( u8 a, u8 b )
{
    u8 tmp1 = ( a | b );
    F = PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}

/**
 * Basic Shift CPU Operations:
 */
u8 Z80::rlc8( u8 v )
{
    u8 tmp1 = ( v << 1 );
    F = ( v >> 7 ); /* All flags to zero, C = bit7 */
    tmp1 |= ( F &1 );
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::rrc8( u8 v )
{
    u8 tmp1 = v >> 1;
    F = ( v &1 ); /* Set Carry from bit0*/
    tmp1 |= ( F << 7 ); /* Set outgoing bit0 in bit7 */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::rl8( u8 v )
{
    u8 tmp1 = (( v << 1 ) | ( F &1 ));
    F = v >> 7; /* F = bit7 */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::rr8( u8 v )
{
    u8 c = ( F & 1 );
    F = v & 1; /* bit0 -> Carry */
    u8 tmp1 = ( v >> 1 ) | ( c << 7 ); /* Old Carry -> bit7 */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::sla8( u8 v )
{
    F = ( v >> 7 );
    u8 tmp1 = ( v << 1 );
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}

/* Undocumented 0xCB30 opcode. Support Undocumented flags. Tested. */
u8 Z80::sll8( u8 v )
{
    F = ( v >> 7 );
    u8 tmp1 = ( v << 1 );
    tmp1 |= 1; /* The only difference with sla8 */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::sra8( u8 v )
{
    F = ( v &1 ); /* Bit0 -> Carry */
    u8 tmp1 = ( v >> 1 );
    tmp1 |= ( v &0x80 ); /* Bit7 is keep unchanged */
    F |= PF_SF_ZF_[tmp1];
//    F |= ( tmp1 &( YF | XF )); /* undocumented flag bits 5+3 */
    return tmp1;
}


u8 Z80::srl8( u8 v )
{
    F = v & 1; /* Bit0 -> Carry*/
    v >>= 1; /* Compute Value */
    F |= PF_SF_ZF_[v];
//    F |= ( v &( YF | XF )); /* undocumented flag bits 5+3 */
    return v;
}

void Z80::rrd()
{
    u8 tmp1 = env.rd8( getHL());
    u8 tmp2 = tmp1;
    tmp1 = ( tmp1 >> 4 ) | ( A << 4 );
    A = ( A &0xf0 ) | ( tmp2 &0xf );
    env.wr8( getHL(), tmp1 &0xff );
    F = F &1;
    F |= PF_SF_ZF_[A];
//    F |= ( A &( YF | XF )); /* undocumented flag bits 5+3 */
    cycleCount += 18;
}

void Z80::rld()
{
    u8 tmp1 = env.rd8( getHL());
    u8 tmp2 = tmp1;
    tmp1 = ( tmp1 << 4 ) | ( A &0xf );
    A = ( A &0xf0 ) | ( tmp2 >> 4 );
    env.wr8( getHL(), tmp1 &0xff );
    F = F &1;
    F |= PF_SF_ZF_[A];
//    F |= ( A &( YF | XF )); /* undocumented flag bits 5+3 */
    cycleCount += 18;
}

/**
 * Basic Bit CPU Operations:
 */
void Z80::bit( u8 bit, u8 v )
{
    // Based on Sean Young documentation, "Z80-documented".
    F = ( F & CF ) | HF; // Clear all bits except CF, HF (always set) from F.
    if ( !( v &( 1 << bit ))) F |= ( ZF | PF ); // ZF is set if tested bit is reset.PF is like ZF.
    if (( bit == 7 ) && !( F &ZF )) F |= SF;   // if tested bit is 7 is set, set SF
//    if(( bit == 5 ) && !( F &ZF )) F |= YF;    // if tested bit is 5 is set, set YF UNDOC Flag
//    if(( bit == 3 ) && !( F &ZF )) F |= XF;    // if tested bit is 3 is set, set XF UNDOC Flag
}

u8 Z80::set( u8 bit, u8 v )
{
    return ( v |= bitval[bit] );
}

u8 Z80::res( u8 bit, u8 v )
{
    return ( v &= ~bitval[bit] );
}

/**
 * Basic Stack CPU Operations:
 */
u16 Z80::pop()
{
    u16 tmp1 = env.rd16( SP );
    SP += 2;
    return ( tmp1 );
}

void Z80::push( u16 val )
{
    SP -= 2;
    env.wr16( SP, val );
}

void Z80::rst( u16 ea )
{
    cycleCount += 11;
    push( PC );
    PC = ea;
}

void Z80::setFlagAfterInput( u8 readed )
{
    F = ( F & CF ); /* Save the Carry Flag */
    F |= PF_SF_ZF_[readed];
}

void Z80::invalid_opcode()
{
    PC--;
    step();          // Execute opcode from standard opcode table.
    cycleCount += 4; // Timing penality.
    printf ("Inv Opc\n");
}

void Z80::invalid_prefixed_opcode()
{
    PC--;
    step();          // Execute opcode from standard opcode table.
    cycleCount += 8; // Timing penality.
    printf ("Inv Opc\n");
}

void Z80::nop()
{
    cycleCount += 4;
}

/* This method generates a Non Maskable interrupt */
void Z80::nmi()
{
    cpuHalted = false; /* UnHalt the cpu.			*/
    IFF1 = false; /* Disable interrupt.			 */
    push( PC ); /* Make call 0x66 			*/
    PC = 0x0066;
    cycleCount += 11;
}

/*
This method generates a Non Maskable interrupt. If cpu accept interrupt
the method returns true, else, interrupt are disabled and the method returns false.
 */
bool Z80::interrupt( u8 data )
{
    if ( IFF1 )
    {
#ifdef BUILT_IN_DEBUGGER
        throwDebugEvent(DbgEvtCpuIrqAsserted, "CPU", "IRQ Asserted: CPU accepts it (DI).");
#endif
        /* Interrupts are enabled */
        cpuHalted = false; // UnHalt the CPU.
        IFF1 = IFF2 = false; // Disable Maskable interrupt
        switch ( IM )
        {
            case 0:
                (this->*(Opc_std[data]))(); // Exec opcode pushed on the bus (data).
                cycleCount += 13;
                break;
            case 1:
                push( PC );
                PC = 0x38;
                cycleCount += 13;
                break;
            case 2:
                push( PC );
                PC = env.rd16((I << 8) | (data & 0xFE));
                cycleCount += 19;
                break;
        }
        return true;
    }
    else
    {
#ifdef BUILT_IN_DEBUGGER
        throwDebugEvent(DbgEvtCpuIrqAsserted, "CPU", "IRQ Asserted: CPU refuse it (DI).");
#endif
        return false;
    }
}

/* Execute one single instruction. */
void Z80::step()
{
    R++;
    if ( cpuHalted == true )
    {
        cycleCount += 4;
    }
    else
    {
        //env.disasm(PC);
        u8 instruction = env.rd8( PC++ );
        (this->*(Opc_std[instruction]))();
#ifdef OPCODES_STATS
        NO_Prefix[ instruction ]++;
#endif
    }
}

u32 Z80::run( u32 wanted_cycles )
{
    u8 instruction;   // Current Opcode
    u32 tc = cycleCount + wanted_cycles;

    while ( cycleCount < tc )
    {
#ifdef BUILT_IN_DEBUGGER
        throwDebugEvent(DbgEvtCpuStep, "CPU", "CPU step.");
#endif
        R++;
        if ( cpuHalted )
        {
            /* Instead of looping doing NOP, compute How many nop to do */
            /* and adjust cycleCount and R accordingly. NOP is 4 cycles.*/
            /* cycleCount += 4; */
            u32 n = ((tc +3 - cycleCount) / 4);
            R += n;
            cycleCount += n * 4;
        }
        else
        {
            instruction = env.rd8( PC++ );
            (this->*(Opc_std[instruction]))();
#ifdef OPCODES_STATS
            NO_Prefix[ instruction ]++;
#endif
        }
    }
    return cycleCount - tc; // overcycles !
}

void Z80::dumpSaveStateStructure(Z80SaveState &css)
{
    cout << "Save state structure dump:" << endl << endl;
    cout << hex << "css.A = " << (unsigned short) css.A << endl;
    cout << "css.F = " << (unsigned short)css.F << endl;
    cout << "css.B = " << (unsigned short)css.B << endl;
    cout << "css.C = " << (unsigned short)css.C << endl;
    cout << "css.D = " << (unsigned short) css.D << endl;
    cout << "css.E = " << (unsigned short)css.E << endl;
    cout << "css.H = " << (unsigned short)css.H << endl;
    cout << "css.L = " << (unsigned short)css.L << endl;
    cout << "css.I = " << (unsigned short)css.I << endl;
    cout << "css.R = " << (unsigned short)css.R << endl;

    cout << "css.A1 = " << (unsigned short)css.A1 << endl;
    cout << "css.F1 = " << (unsigned short)css.F1 << endl;
    cout << "css.B1 = " << (unsigned short)css.B1 << endl;
    cout << "css.C1 = " << (unsigned short)css.C1 << endl;
    cout << "css.D1 = " << (unsigned short)css.D1 << endl;
    cout << "css.E1 = " << (unsigned short)css.E1 << endl;
    cout << "css.H1 = " << (unsigned short)css.H1 << endl;
    cout << "css.L1 = " << (unsigned short)css.L1 << endl;
    cout << "css.Rbit7 = " << (unsigned short)css.Rbit7 << endl;

    cout << "css.IM = " << (unsigned short)css.IM << endl;
    cout << "css.PC = " << (unsigned short)css.PC << endl;
    cout << "css.IX = " << (unsigned short)css.IX << endl;
    cout << "css.IY = " << (unsigned short)css.IY << endl;
    cout << "css.SP = " << (unsigned short)css.SP << endl;
    cout << "css.IFF1 = " << css.IFF1 << endl;
    cout << "css.IFF2 = " << css.IFF2 << dec << endl;
    cout << "css.cpuHalted  = " << (unsigned int) css.cpuHalted << endl;
    cout << "css.cycleCount = " << (unsigned int) css.cycleCount << endl << endl;
}


void Z80::dumpValues()
{
    cout << "CPU register dump:" << endl << endl;
    cout << hex << "A = " << (unsigned short) A << endl;
    cout << "F = " << (unsigned short)F << endl;
    cout << "B = " << (unsigned short)B << endl;
    cout << "C = " << (unsigned short)C << endl;
    cout << "D = " << (unsigned short)D << endl;
    cout << "E = " << (unsigned short)E << endl;
    cout << "H = " << (unsigned short)H << endl;
    cout << "L = " << (unsigned short)L << endl;
    cout << "I = " << (unsigned short)I << endl;
    cout << "R = " << (unsigned short)R << endl;

    cout << "A1 = " << (unsigned short)A1 << endl;
    cout << "F1 = " << (unsigned short)F1 << endl;
    cout << "B1 = " << (unsigned short)B1 << endl;
    cout << "C1 = " << (unsigned short)C1 << endl;
    cout << "D1 = " << (unsigned short)D1 << endl;
    cout << "E1 = " << (unsigned short)E1 << endl;
    cout << "H1 = " << (unsigned short)H1 << endl;
    cout << "L1 = " << (unsigned short)L1 << endl;
    cout << "Rbit7 = " << (unsigned short)Rbit7 << endl;

    cout << "IM = " << (unsigned short)IM << endl;
    cout << "PC = " << (unsigned short)PC << endl;
    cout << "IX = " << (unsigned short)IX << endl;
    cout << "IY = " << (unsigned short)IY << endl;
    cout << "SP = " << (unsigned short)SP << endl;
    cout << "IFF1 = " << (unsigned short)IFF1 << endl;
    cout << "IFF2 = " << (unsigned short)IFF2 << dec << endl;
    cout << "cpuHalted  = " << (unsigned int)cpuHalted << endl;
    cout << "cycleCount = " << (unsigned int)cycleCount << endl << endl;
}

bool Z80::saveState( ofstream &ofs )
{
    Z80SaveState css;

    css.A = A;
    css.F = F;
    css.B = B;
    css.C = C;
    css.D = D;
    css.E = E;
    css.H = H;
    css.L = L;
    css.I = I;
    css.R = R;
    css.A1 = A1;
    css.F1 = F1;
    css.B1 = B1;
    css.C1 = C1;
    css.D1 = D1;
    css.E1 = E1;
    css.H1 = H1;
    css.L1 = L1;
    css.Rbit7 = Rbit7;
    css.IM = IM;
    css.PC = PC;
    css.IX = IX;
    css.IY = IY;
    css.SP = SP;
    css.IFF1 = IFF1;
    css.IFF2 = IFF2;
    css.cpuHalted = cpuHalted;
    css.cycleCount = cycleCount;

    ofs.write((char *)&css, sizeof(css));
    //dumpValues();
    //dumpSaveStateStructure(css);
    return ofs.good();
}

bool Z80::loadState( ifstream &ifs )
{
    Z80SaveState css;
    bool ret = false;

    ifs.read((char *)&css, sizeof(css));
    ret = ifs.good();

    //dumpSaveStateStructure(css);

    /* Don't restore the values if read fails ! */
    if (!ret) return false;

    A = css.A;
    F = css.F;
    B = css.B;
    C = css.C;
    D = css.D;
    E = css.E;
    H = css.H;
    L = css.L;
    I = css.I;
    R = css.R;
    A1 = css.A1;
    F1 = css.F1;
    B1 = css.B1;
    C1 = css.C1;
    D1 = css.D1;
    E1 = css.E1;
    H1 = css.H1;
    L1 = css.L1;
    Rbit7 =css.Rbit7;
    IM = css.IM;
    PC = css.PC;
    IX = css.IX;
    IY = css.IY;
    SP = css.SP;
    IFF1 = css.IFF1;
    IFF2 = css.IFF2;
    cpuHalted = css.cpuHalted;
    cycleCount = css.cycleCount;
    //dumpValues();
    return true;
}
