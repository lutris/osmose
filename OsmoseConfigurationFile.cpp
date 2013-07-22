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
 * File : OsmoseConfigurationFile.cpp
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Fri Nov 26 15:50:00 2010
 *
 */

#include "OsmoseConfigurationFile.h"

/**
 * Constructor.
 */
OsmoseConfigurationFile::OsmoseConfigurationFile()
{
	homeDir = OsmoseConfigurationFile::getHomeDirectory();
}

/**
 * Return the user's home directory. It first checks into the pw 
 * structure and then in HOME envirnoment variable. If $HOME exists
 * it is taken first.
 */
string OsmoseConfigurationFile::getHomeDirectory()
{
	struct passwd *pw = getpwuid(getuid());
	string homeDirectory = string(pw->pw_dir);
	
	// If $HOME variable exists, override homeDirectory with its content.
	string user_home_directory = string (getenv("HOME"));
	if (!user_home_directory.empty())
	{
		homeDirectory = string(user_home_directory.c_str());
	}
	
	return homeDirectory;
}


/**
 * Destructor.
 */
OsmoseConfigurationFile::~OsmoseConfigurationFile()
{
}

/**
 * Load the configuration file. Throws an exception in case of problem.
 */
void OsmoseConfigurationFile::load()
{
	string fullname = homeDir + "/.osmose2.ini";	
	ifstream file(fullname.c_str(), ios::in);

	if (file.is_open() == false )
    {
		string msg = "Unable to load '";
		msg = msg + fullname + "' configuration file.";
        throw string(msg);
	}
	
	// Parse the config file and update members.
	string line;
    while ( file.good() )
    {
		getline (file,line);
		parseLine(line);
    }
	file.close();
}

/**
 * Receive a line from configuration file. If it contains a valid  identifier
 * and value, the corresponding member value is updated. Every symbols after
 * '#' char are considered to be commented out.
 */
void OsmoseConfigurationFile::parseLine(string &line)
{
	// Remove beginning space and control char if any.
	while((line[0] <= ' ') && (line.length() != 0)) line.erase(0, 1);
	
	// Remove all after '#' char if any.
	size_t pos = line.find('#', 0);
	if (pos != string::npos) line.erase(pos);
	
	// Remove all control chars in the string.
	pos = 0;
	while ((pos < line.length()) && (line.length() > 0))
	{
		while((line[pos] <= ' ') && (pos < line.length()))
		{
			line.erase(pos, 1);
		}
		pos++;
	}
	
	// Extract identifier from line[0] to char '='.
	pos = line.find('=', 0);
	if (pos == string::npos) return; 	// No '=' char found.
	
	string identifier = line.substr(0, pos);
	
	// Extract value between two simple quotes.
	pos = line.find('\'', 0);
	if (pos == string::npos) return; 	// No '\'' char found. 
	pos++; // Index of first char after '
	
	size_t pos2 = line.find('\'', pos);
	if (pos2 == string::npos) return; 	// No second '\'' char found. 
	
	string value = line.substr(pos, pos2-pos);
	updateItem(identifier, value);
}

/**
 * This method extract new value and affects it to the concerned identifier.
 * If identifier is unknown, or value not parsable, an error string is thrown\
 * via an exception.
 */
void OsmoseConfigurationFile::updateItem(string &identifier, string &value)
{
	if (identifier == "ScreenshotPath")
	{
		screenshotPath = value;
		return;
	}
	else
	if (identifier == "SaveStatePath")
	{
		saveStatePath = value;
		return;
	}
	else
	if (identifier == "SoundCapturePath")
	{
		soundCapturePath = value;
		return;
	}
	else
	if (identifier == "TileCapturePath")
	{
		tileCapturePath = value;
		return;
	}
	else
	if (identifier == "BatteryBackedRAMPath")
	{
		BBRPath = value;
		return;
	}
	else
	if (identifier == "JoystickDevice")
	{
		joystickDevice = value;
		return;
	}
	
	// At this point, value is interepreted only as ascii int.
	// Basic verification.
	for (unsigned int i=0; i < value.length(); i++)
	{
		if ((value[i] < '0' || value[i]>'9') && value[i] != '-')
		{
			string msg = "Unable to extract value for ";
			msg = msg + identifier;
			msg = msg + " : value is ";
			msg = msg + value;
			throw string(msg);
		}
	}
	
	istringstream iss(value, istringstream::in);
	int int_value;
	iss >> int_value;
	
	if (identifier == "Player1Up")
	{
		setPad(0, UP, int_value);
		return;
	}
	else
	if (identifier == "Player1Down")
	{
		setPad(0, DOWN, int_value);
		return;
	}
	else
	if (identifier == "Player1Left")
	{
		setPad(0, LEFT, int_value);
		return;
	}	
	else
	if (identifier == "Player1Right")
	{
		setPad(0, RIGHT, int_value);
		return;
	}
	else
	if (identifier == "Player1ButtonA")
	{
		setPad(0, BUTTON_A, int_value);
		return;
	}	
	else
	if (identifier == "Player1ButtonB")
	{
		setPad(0, BUTTON_B, int_value);
		return;
	}	
	
	if (identifier == "Player2Up")
	{
		setPad(1, UP, int_value);
		return;
	}
	else
	if (identifier == "Player2Down")
	{
		setPad(1, DOWN, int_value);
		return;
	}
	else
	if (identifier == "Player2Left")
	{
		setPad(1, LEFT, int_value);
		return;
	}	
	else
	if (identifier == "Player2Right")
	{
		setPad(1, RIGHT, int_value);
		return;
	}
	else
	if (identifier == "Player2ButtonA")
	{
		setPad(1, BUTTON_A, int_value);
		return;
	}	
	else
	if (identifier == "Player2ButtonB")
	{
		setPad(1, BUTTON_B, int_value);
		return;
	}	
	else
	if (identifier == "Pause")
	{
		pauseButton = int_value;
		
		return;
	}	
	else
	if (identifier == "Start")
	{
		startButton = int_value;
		return;
	}
	else
	if (identifier == "Joy0Button0")
	{
		joystick0Button[0] = (padKey)int_value;
		return;
	}
	else
	if (identifier == "Joy0Button1")
	{
		joystick0Button[1] = (padKey)int_value;
		return;
	}	
	else
	if (identifier == "Joy0Button2")
	{
		joystick0Button[2] = (padKey)int_value;
		return;
	}	
	else
	if (identifier == "Joy0Button3")
	{
		joystick0Button[3] = (padKey)int_value;
		return;
	}	
	else
	if (identifier == "Joy0Button4")
	{
		joystick0Button[4] = (padKey)int_value;
		return;
	}
	else
	if (identifier == "Joy0Button5")
	{
		joystick0Button[5] = (padKey)int_value;
		return;
	}	
	else
	if (identifier == "Joy0Button6")
	{
		joystick0Button[6] = (padKey)int_value;
		return;
	}	
	else
	if (identifier == "Joy0Button7")
	{
		joystick0Button[7] = (padKey)int_value;
		return;
	}	
	
	// At this point identifier is unknown !
	string msg = "Unknown identifier :";
	msg = msg + identifier;
	throw string(msg);	
	
}




/**
 * Save the configuration file. Throws an exception in case of problem.
 */
void OsmoseConfigurationFile::save()
{
		string fullname = homeDir + "/.osmose2.ini";
        ofstream file(fullname.c_str(), ios::out);
        if (file.is_open() == false )
        {
			string msg = "Unable to write '";
			msg = msg + fullname + "' configuration file.";
            throw string(msg);
        
        }
        else // Default ini file creation
        {
            file << "#" << endl << "# Osmose Sega MasterSystem/Gamegear emulator configuration file." << endl;
			file << "# Identifiers are case sensitive, do not edit this file manually," << endl;
			file << "# it will be overwritten in case of error or configuration change !" << endl << "#" << endl << endl;
			file << "ScreenshotPath       = '" << screenshotPath << "'" << endl;
			file << "SaveStatePath        = '" << saveStatePath << "'" << endl;
			file << "SoundCapturePath     = '" << soundCapturePath << "'" << endl;
			file << "TileCapturePath      = '" << tileCapturePath << "'" << endl;
			file << "BatteryBackedRAMPath = '" << BBRPath << "'" << endl << endl;
			
			file << "#" << endl << "# Played 1 Pad:" << endl << "#" << endl << endl;
			file << "Player1Up      = '" << (int) pad1[UP] << "'" << endl;
			file << "Player1Down    = '" << (int) pad1[DOWN] << "'" << endl;
			file << "Player1Left    = '" << (int) pad1[LEFT] << "'" << endl;
			file << "Player1Right   = '" << (int) pad1[RIGHT] << "'" << endl;
			file << "Player1ButtonA = '" << (int) pad1[BUTTON_A] << "'" << endl;
			file << "Player1ButtonB = '" << (int) pad1[BUTTON_B] << "'" << endl << endl;

			file << "#" << endl << "# Played 2 Pad:" << endl << "#" << endl << endl;
			file << "Player2Up      = '" << (int) pad2[UP] << "'" << endl;
			file << "Player2Down    = '" << (int) pad2[DOWN] << "'" << endl;
			file << "Player2Left    = '" << (int) pad2[LEFT] << "'" << endl;
			file << "Player2Right   = '" << (int) pad2[RIGHT] << "'" << endl;
			file << "Player2ButtonA = '" << (int) pad2[BUTTON_A] << "'" << endl;
			file << "Player2ButtonB = '" << (int) pad2[BUTTON_B] << "'" << endl << endl;
			
			file << "#" << endl << "# Pause, Gamer Gear Start :" << endl << "#" << endl << endl;
			file << "Pause      = '" << (int) pauseButton << "'" << endl;
			file << "Start      = '" << (int) startButton << "'" << endl << endl;

			file << "#" << endl << "# Joystick 0 buttons assignations :" << endl << "#" << endl << endl;
			for (int i=0; i < MAX_JOYSTICK_BUTTON ; i++)
			{
				file << "Joy0Button" << (int) i << " = '"<< (int) joystick0Button[i] << "'" << endl;			
			}
			
			file << endl << "#" << endl << "# Joystick Linux device :" << endl << "#" << endl << endl;
			file << "JoystickDevice = '" << joystickDevice << "'" << endl;			
		}
		file << endl << endl;
		file.close();
}

/**
 * Restore Osmose default configuration of Pathes and key mapping.
 */
void OsmoseConfigurationFile::resetToDefault()
{
	saveStatePath   = homeDir;
	soundCapturePath= homeDir;
	tileCapturePath = homeDir;
	BBRPath			= homeDir;
	screenshotPath	= homeDir;
	
	pad1[UP]    = 16777235;		// Up arrow.
	pad1[DOWN]  = 16777237;		// Down arrow.
	pad1[LEFT]  = 16777234;		// Left arrow.
	pad1[RIGHT] = 16777236;		// Right arrow.
	pad1[BUTTON_A] = 90;		// Z key.
	pad1[BUTTON_B] = 88;		// X key.

	pad2[UP]    = 56;			// KeyPad/Keyboard 8.
	pad2[DOWN]  = 50;			// KeyPad/Keyboard 2.
	pad2[LEFT]  = 52;			// KeyPad/Keyboard 4.
	pad2[RIGHT] = 54;			// KeyPad/Keyboard 6.
	pad2[BUTTON_A] = 48;		// KeyPad/Keyboard 0.
	pad2[BUTTON_B] = 16777221;	//KeyPad/Keyboard Enter.
	
	startButton = 83; 			// S key.
	pauseButton = 80;  			// P key.
	
	joystick0Button[0] = P1BUTTON_A;
	joystick0Button[1] = P1BUTTON_B;
	joystick0Button[2] = START_GG;
	joystick0Button[3] = PAUSE_NMI;
	joystick0Button[4] = UNKNOWN;
	joystick0Button[5] = UNKNOWN;
	joystick0Button[6] = UNKNOWN;
	joystick0Button[7] = UNKNOWN;
	
	joystickDevice = string(DEFAULT_JOYSTICK_DEVICE);
}

/**
 * Restore Osmose default configuration of Pathes and key mapping and save
 * the configuration file.
 */
void OsmoseConfigurationFile::createDefautConfigurationFile()
{
	resetToDefault();
	save();
}

/**
 * This method associate pad direction or button to a key binding.
 * Param1 : Pad number 0 = first, other is second pad.
 * Param2 : Direction or Button enum to map to a QT key.
 * Param3 : The Qt key ID associated to the pad touch.
 */
void OsmoseConfigurationFile::setPad(int padNumber, padInput i, unsigned int key)
{
	if (padNumber == 0)
	{
		pad1[i] = key;		
	}
	else
	{
		pad2[i] = key;
	}
}


/**
 * This method returns key associated to a pad direction.
 * Param1 : Pad number 0 = first, other is second pad.
 * Param2 : Direction or Button enum to map to a QT key.
 */
int OsmoseConfigurationFile::getPad(int padNumber, padInput i)
{
	if (padNumber == 0)
	{
		return pad1[i];
	}
	else
	{
		return pad2[i];
	}
}

/**
 * This method set key associated to a joystick button.
 * Param1 : button number.
 * Param2 : SMS equivalent key.
 */
void OsmoseConfigurationFile::assignJoyButton(int button, padKey assignation)
{
	if (button  >=0 && button < MAX_JOYSTICK_BUTTON)
	{
		joystick0Button[button] = assignation;
	}
}

padKey OsmoseConfigurationFile::getJoyButtonAssignation(int button)
{
	if ((button  >=0) && (button < MAX_JOYSTICK_BUTTON))
	{
		return joystick0Button[button];
	}
	return UNKNOWN;
}

/** 
 * This method convert the key pressed to SMS/GG key pad, depending on
 * the actual configuration.
 */
padKey OsmoseConfigurationFile::keyToKeyPad(int key)
{
	if (key == pad1[0]) return P1UP;
	if (key == pad1[1]) return P1DOWN;
	if (key == pad1[2]) return P1LEFT;
	if (key == pad1[3]) return P1RIGHT;
	if (key == pad1[4]) return P1BUTTON_A;
	if (key == pad1[5]) return P1BUTTON_B;
	
	if (key == pad2[0]) return P2UP;
	if (key == pad2[1]) return P2DOWN;
	if (key == pad2[2]) return P2LEFT;
	if (key == pad2[3]) return P2RIGHT;
	if (key == pad2[4]) return P2BUTTON_A;
	if (key == pad2[5]) return P2BUTTON_B;

	if (key == pauseButton) return PAUSE_NMI;
	if (key == startButton) return START_GG;
	
	return UNKNOWN;
}



