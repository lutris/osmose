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
 * File : QOsmoseConfiguration.h
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Sun Nov 21 16:21:21 2010
 *
 */

#ifndef QOSMOSECONFIGURATION_H
#define QOSMOSECONFIGURATION_H

#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_Configuration.h"
#include "KeyMapper.h"
#include "Joystick.h"
#include "OsmoseConfigurationFile.h"

class KeyGrabber : public QDialog
{

Q_OBJECT

public:
	KeyGrabber(QWidget *parent = 0);
	unsigned int getKeyPressed() {return keyPressed;}
	
protected:
	void keyPressEvent(QKeyEvent *e);
	unsigned int keyPressed;
};

class QOsmoseConfiguration : public QDialog, public JoystickListener, private Ui::Configuration
{

Q_OBJECT

public:

	QOsmoseConfiguration(OsmoseConfigurationFile *conf, const char *joyName, QWidget *parent = 0);
	void synchronizeWithConfiguration();
	
	// Joystick listener interface.
	void buttonChanged(unsigned int button, bool pressed); /* True when pressed */
    void xAxisChanged(int value);
	void yAxisChanged(int value);
	void joystickError();	
	
	
	~QOsmoseConfiguration();

protected:

public slots:
	void selectBBRPath();
	void selectScreenshotPath();
	void selectSaveStatePath();	
	void selectTileRipPath();	
	void selectSoundRipPath();	

	void redefineP1Up();
	void redefineP1Down();
	void redefineP1Left();
	void redefineP1Right();
	void redefineP1A();
	void redefineP1B();

	void redefineP2Up();
	void redefineP2Down();
	void redefineP2Left();
	void redefineP2Right();
	void redefineP2A();
	void redefineP2B();
	
	void redefinePause();
	void redefineStart();
	
	void saveConfiguration();
	void applyConfiguration();

	void joy0Button1Assigned(int assign);
	void joy0Button2Assigned(int assign);
	void joy0Button3Assigned(int assign);
	void joy0Button4Assigned(int assign);
	void joy0Button5Assigned(int assign);
	void joy0Button6Assigned(int assign);
	void joy0Button7Assigned(int assign);
	void joy0Button8Assigned(int assign);
	
	void joyButton1Changed(bool pressed);
	void joyButton2Changed(bool pressed);
	void joyButton3Changed(bool pressed);
	void joyButton4Changed(bool pressed);
	void joyButton5Changed(bool pressed);
	void joyButton6Changed(bool pressed);
	void joyButton7Changed(bool pressed);
	void joyButton8Changed(bool pressed);
	
signals:
	void joyButton1Event(bool pressed);
	void joyButton2Event(bool pressed);
	void joyButton3Event(bool pressed);	
	void joyButton4Event(bool pressed);
	void joyButton5Event(bool pressed);	
	void joyButton6Event(bool pressed);	
	void joyButton7Event(bool pressed);	
	void joyButton8Event(bool pressed);
	
private:
	void completeConnections();
	unsigned int pickupKey(QLabel *label);
	int buttonAssignationToComboBox(padKey k);
	padKey comboBoxToButtonAssignation(int);
	QString homeDirectory;
	OsmoseConfigurationFile *ocf;
};

#endif	// QOSMOSECONFIGURATION_H
