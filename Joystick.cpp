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
 * File : Joystick.cpp
 *
 * Description : This class inherits from Thread and read, every
 * polling period, the device file given to it's constructor. If events
 * are detected, the listener joystickChanged method will be called.
 * Note that several events will generate several call to joystick 
 * changed. There's only one listener at a time.
 *
 * Author : B.Vedder
 *
 * Date : Wed Dec 29 08:36:46 2010
 *
 */

#include "Joystick.h"

/**
 * Constructor. Throw an exception in case of failure.
 *
 * Param1 : The device name to read from. e.g: /dev/input/js0
 * Param2 : The JoystickListener that will be notified with jostick events
 *
 */
Joystick::Joystick(char *dev_name, JoystickListener *lstnr)
{
	mutex = PTHREAD_MUTEX_INITIALIZER;

    // Try to open the device.
    joystickFD = ::open(dev_name, O_RDONLY | O_NONBLOCK);
    if (joystickFD < 0)
    {
        string err = "Unable to open device '";
        err = err + dev_name;
        err = err + "' : ";
        err = err + strerror(errno);
        throw err;
    }
    
    // Device successfully opened. Keep track of device name.
    ::strncpy(deviceName, dev_name, MAX_DEVNAME_LEN);
    
    // Now get Joystick ID.
    if (::ioctl(joystickFD, JSIOCGNAME(MAX_JOYID_LEN), joystickID) < 0)
    {
		::strncpy(joystickID, "Unknown", MAX_JOYID_LEN);
	}

	// Now get button number.
    if (::ioctl(joystickFD, JSIOCGBUTTONS, &buttonNbr) < 0)
    {
		buttonNbr = 0;
	}	
	
    // Now get Axis number.
    if (::ioctl(joystickFD, JSIOCGAXES, &axisNbr) < 0)
    {
		axisNbr = 0;
	}

    // Now get driver version.
    if (::ioctl(joystickFD, JSIOCGVERSION, &driverVersion) < 0)
    {
		driverVersion = 0xFFFFFFFF;
	}
	
    // Keep track of listener for upcoming events.
    setListener(lstnr);
    
    // Set default polling period.
    setPollingPeriod(DEFAULT_POLLING_PERIOD); // in milliseconds.

	// Start device polling.
	done = false;
	this->start();
}

/**
 * setPollingPeriod:
 *
 * Param1 : the delay between two non blocking read on the device file.
 * Unit is millisecond. If value is negative or equal to zero, the default
 * polling period will be used.
 *
 */
void Joystick::setPollingPeriod(int pp_ms)
{
    pollingPeriod = (pp_ms <= 0) ? DEFAULT_POLLING_PERIOD: pp_ms;
}

/**
 * This method reads the joystick file descriptor for new events.
 * return true if an event has been read, false otherwise. Unfortunatelly,
 * no data, and joystick unplugged return the same error 11 : 
 * 'Resource temporarily unavailable'. We cannot simply detect if joystick
 * is present or not.
 */
bool Joystick::readDevice(struct js_event *jse)
{
	int bytes_read;
	
	bytes_read = read(joystickFD, jse, sizeof(*jse)); 
	
	// Handle errors !!!
	if (bytes_read == -1)
	{
		return false;
	}
	return true;
}


/**
 * Thread main loop :
 * This is the polling routine of the joystick handler.
 */
void *Joystick::run(void *)
{
	struct timespec rqtp, rmtp;
    struct js_event jse;
	
	while(!done)
    {
		// read the Joystick file descriptor until no more events are available.
		while (readDevice(&jse) == true)
		{
			if (jse.type & 0x80) continue;	// Skip JS_EVENT_INIT (0x80) events.
			switch(jse.type)
			{
				case JS_EVENT_BUTTON:
				{
					// Inform the listener that button event occurs.
					bool pressed = (jse.value !=  0);
					listener->buttonChanged(jse.number, pressed);
				}
				break;
				
				case JS_EVENT_AXIS:
				{
					// Inform the listener that axis event occurs.
					switch(jse.number)
					{
						case 0:
							listener->xAxisChanged(jse.value);
						break;
						case 1:
							listener->yAxisChanged(jse.value);
						break;				
					}
				}
				break;
								
				default:
				break;
			}
		} // No more event to handle.
		
		
		// Sleep for the polling period.
		rqtp.tv_sec = 0;
		rqtp.tv_nsec = pollingPeriod * 1000 * 1000; 	
		nanosleep(&rqtp, &rmtp);
    }
    return NULL;
}

/**
 *
 * Destructor. Throw an exception in case of failure.
 *
 */
Joystick::~Joystick()
{
	done = true;
	this->join(NULL);
    ::close(joystickFD);
}

