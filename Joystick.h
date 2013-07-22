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
 * File : Joystick.h
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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <linux/joystick.h>
#include "Pthreadcpp.h"

using namespace std;

#define MAX_DEVNAME_LEN	128
#define MAX_JOYID_LEN	128
#define DEFAULT_POLLING_PERIOD	  3


/**
 * Joystick listener interface.
 * Inherit this class and provide virtual methods in order to be a full Joystick listener.
 */
class JoystickListener
{
public:
	virtual void buttonChanged(unsigned int button, bool pressed) = 0; /* True when pressed */
    virtual void xAxisChanged(int value) = 0;
	virtual void yAxisChanged(int value) = 0;
	virtual void joystickError() = 0;
};

class Joystick : public Thread
{
public:
    
	Joystick(char *dev_name, JoystickListener *l);
    const char * getStrID() { return joystickID;  }
    const char * getDeviceName() { return deviceName; }
    void setListener(JoystickListener *lstnr) { listener = lstnr; }
    void setPollingPeriod(int ms);
    int  getPollingPeriod() { return pollingPeriod; }
	unsigned int getAxisNumber() { return (unsigned int)axisNbr; }
	unsigned int getButtonNumber() { return (unsigned int)buttonNbr; }
	unsigned int getDriverVersion() {return driverVersion; }
    ~Joystick();
    
protected:
    
	void *run(void *);
    
private:
    
	char deviceName[MAX_DEVNAME_LEN];
    char joystickID[MAX_JOYID_LEN];
    int  joystickFD;
	unsigned char axisNbr;
	unsigned char buttonNbr;
	unsigned int  driverVersion; // Unused-Major-Minor-Lower 8 bits packed.
	
    JoystickListener *listener;
    int pollingPeriod;
	bool done;
	pthread_mutex_t mutex;

	bool readDevice(struct js_event *jse);
	
};

#endif	// JOYSTICK_H
