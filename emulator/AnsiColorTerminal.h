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
 * File: AnsiTer,inalColors.h
 * Project: Osmose emulator.
 *
 * Description: These MACROS allows the program to output colored strings on
 * the terminal. Note that only basic coloring is handled, not the full escape
 * sequences defined by the norm. SO Bold chars, video inverse and blinking
 * things do not work.
 *
 * Note that USE_ISO_IEC_6429 must be define in order to work. Undefine this
 * setting for non ISO6429 compliant terminal (ms win).
 *
 * Author: Vedder Bruno
 * Date: 12/12/2007
 * URL: http://bcz.asterope.fr
 */
 
#ifndef ANSI_TERMINAL_COLORS_H
#define ANSI_TERMINAL_COLORS_H

#ifdef USE_ISO_IEC_6429
#define BLACK(str)		"\033[0;30;49;1m"<<str<<"\033[0m"
#define RED(str)		"\033[0;31;49;1m"<<str<<"\033[0m"
#define GREEN(str)		"\033[0;32;49;1m"<<str<<"\033[0m"
#define YELLOW(str)		"\033[0;33;49;1m"<<str<<"\033[0m"
#define BLUE(str)		"\033[0;34;49;1m"<<str<<"\033[0m"
#define MAGENTA(str)		"\033[0;35;49;1m"<<str<<"\033[0m"
#define CYAN(str)		"\033[0;36;49;1m"<<str<<"\033[0m"
#define WHITE(str)		"\033[0;37;49;1m"<<str<<"\033[0m"
#else
#define BLACK(str)		str
#define RED(str)		str
#define GREEN(str)		str
#define YELLOW(str)		str
#define BLUE(str)		str
#define MAGENTA(str)		str
#define CYAN(str)		str
#define WHITE(str)		str
#endif

#endif // ANSI_TERMINAL_COLORS_H
