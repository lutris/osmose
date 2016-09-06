/*
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
 *
 * File: main.cpp
 *
 * Project: Osmose emulator
 *
 * Description:
 *
 * Author: Bruno Vedder
 * Date:
 *
 * URL: http://bcz.asterope.fr
 */

#include <QApplication>
#include <QTextStream>
#include "OsmoseGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    OsmoseGUI window;
    window.resize(512, 384 + MENU_HEIGHT);
    window.show();
    for (int i=1; i < argc; i++) {
        if(QString(argv[i]) == "-f" || QString(argv[i]) == "--fullscreen") {
            window.toggleFullscreen();
        } else {
            QString rom_file = argv[i];
            window.loadTheROM(rom_file);
        }
    }
    return app.exec();
}
