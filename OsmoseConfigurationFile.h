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
 * File : OsmoseConfigurationFile.h
 *
 * Description : This class handle $HOME .osmose.ini file.
 *
 * Author : B.Vedder
 *
 * Date : Fri Nov 26 15:50:00 2010
 *
 */

#ifndef OSMOSECONFIGURATIONFILE_H
#define OSMOSECONFIGURATIONFILE_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

typedef enum
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	BUTTON_A,
	BUTTON_B
} padInput;

typedef enum
{
	P1UP = 0,
	P1DOWN,
	P1LEFT,
	P1RIGHT,
	P1BUTTON_A,
	P1BUTTON_B,
	P2UP,
	P2DOWN,
	P2LEFT,
	P2RIGHT,
	P2BUTTON_A,
	P2BUTTON_B,
	START_GG,
	PAUSE_NMI,
	SCREENSHOT,
	SOUNDSHOT,
	UNKNOWN = 0x80000000

} padKey;

#define MAX_JOYSTICK_BUTTON		8
#define DEFAULT_JOYSTICK_DEVICE "/dev/input/js0"

class OsmoseConfigurationFile
{
	

	
public:
	
	OsmoseConfigurationFile();
	void save();
	void load();
	void createDefautConfigurationFile();
	void resetToDefault();
	padKey keyToKeyPad(int key);
	
	static string getHomeDirectory();
	~OsmoseConfigurationFile();
	
	// Button setters.
	void setPad(int padNumber, padInput i, unsigned int key);
	void setPause(unsigned int key){pauseButton = key;}
	void setStart(unsigned int key){startButton = key;}
	void assignJoyButton(int button, padKey assignation);
	
	// Path setters.
	void setScreenshotPath(string path) {screenshotPath = path;}
	void setSoundCapturePath(string path) {soundCapturePath = path;}
	void setTileCapturePath(string path) {tileCapturePath = path;};
	void setBBRPath(string path) {BBRPath = path;};
	void setSaveStatePath(string path) {saveStatePath = path;};

	// Joystick device setter :
	void setJoystickDevice(string device) { joystickDevice = device; }	
	
	// Button getters.
	int getPad(int padNumber, padInput i);
	int getPause() {return pauseButton;}
	int getStart() {return startButton;}
	padKey getJoyButtonAssignation(int button);

	// Path getters.
	string getScreenshotPath() {return screenshotPath;}
	string getSoundCapturePath() {return soundCapturePath;}
	string getTileCapturePath() {return tileCapturePath;}
	string getBBRPath() {return BBRPath;}
	string getSaveStatePath() {return saveStatePath;}
	
	// Joystick device getter :
	string getJoystickDevice() { return joystickDevice; }
	
protected:

private:
	string homeDir;

	// Osmose configuration data.
	string saveStatePath;
	string soundCapturePath;
	string tileCapturePath;
	string BBRPath;
	string screenshotPath;
	int pad1[6];			// Keyboard Mapping for P1 pad keys: UP:DOW:LEF:RIG:A:B
	int pad2[6];			// Keyboard Mapping for P2 pad keys: UP:DOW:LEF:RIG:A:B
	int startButton; 		// Keyboard Mapping for Start
	int pauseButton;		// Keyboard Mapping for Pause
	padKey joystick0Button[MAX_JOYSTICK_BUTTON]; // Joystick button assignation.
	
	void parseLine(string &l);
	void updateItem(string &identifier, string &value);
	string joystickDevice;
};

#endif	// OSMOSECONFIGURATIONFILE_H
