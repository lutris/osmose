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
 * File : QOsmoseConfiguration.cpp
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Sun Nov 21 16:21:21 2010
 *
 */

#include "QOsmoseConfiguration.h"
#include <iostream>

using namespace std;

/**
 * Constructor.
 */
QOsmoseConfiguration::QOsmoseConfiguration(OsmoseConfigurationFile *conf, const char *joyName, QWidget *parent) : QDialog(parent)
{

	homeDirectory = QString(OsmoseConfigurationFile::getHomeDirectory().c_str());
	setupUi((QDialog*)this);
	completeConnections();
	joystickNameQLabel->setText(joyName);
	ocf = conf;
	synchronizeWithConfiguration();
	this->setFixedSize(this->width(),this->height());
}


/**
 * Destructor.
 */
QOsmoseConfiguration::~QOsmoseConfiguration()
{
	delete ocf;
}


/**
 * selectBBRPath slot :
 *
 * This slot is called when the tool button is clicked. It then open a file
 * selection dialog to get an existing directory to store Battery Backed RAM.
 * The corresponding QLineEdit is also updated with the choosen path.
 */
void QOsmoseConfiguration::selectBBRPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 homeDirectory,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty() || dir.isNull()) return;
	bbrPathLineEdit->setText(dir);                               
}


/**
 * selectScreenshotPath slot :
 *
 * This slot is called when the tool button is clicked. It then open a file
 * selection dialog to get an existing directory to store screenshots.
 * The corresponding QLineEdit is also updated with the choosen path.
 */
void QOsmoseConfiguration::selectScreenshotPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 homeDirectory,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty() || dir.isNull()) return;
	screenshotsPathLineEdit->setText(dir);                               
}


/**
 * selectSaveStatePath slot :
 *
 * This slot is called when the tool button is clicked. It then open a file
 * selection dialog to get an existing directory to store save states.
 * The corresponding QLineEdit is also updated with the choosen path.
 */
void QOsmoseConfiguration::selectSaveStatePath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 homeDirectory,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty() || dir.isNull()) return;
	saveStatePathLineEdit->setText(dir);                               
}


/**
 * selectTileRipPath slot :
 *
 * This slot is called when the tool button is clicked. It then open a file
 * selection dialog to get an existing directory to store ripped tiles.
 * The corresponding QLineEdit is also updated with the choosen path.
 */
void QOsmoseConfiguration::selectTileRipPath()	
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 homeDirectory,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty() || dir.isNull()) return;
	tileSavePathLineEdit->setText(dir);                               
}


/**
 * selectTileRipPath slot :
 *
 * This slot is called when the tool button is clicked. It then open a file
 * selection dialog to get an existing directory to store ripped sounds.
 * The corresponding QLineEdit is also updated with the choosen path.
 */
void QOsmoseConfiguration::selectSoundRipPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 homeDirectory,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty() || dir.isNull()) return;
	soundSavePathLineEdit->setText(dir);                               
}

/**
 * completeConnections() :
 * This method perform the SLOT/SIGNAL connections.
 */
void QOsmoseConfiguration::completeConnections()
{
	// Connect directory file selectors.
	QObject::connect(bbrSelectPath, SIGNAL(clicked()), this, SLOT(selectBBRPath()));
	QObject::connect(screenshotsSelectPath, SIGNAL(clicked()), this, SLOT(selectScreenshotPath()));
	QObject::connect(saveStateSelectPath, SIGNAL(clicked()), this, SLOT(selectSaveStatePath()));
	QObject::connect(tileSaveSelectPath, SIGNAL(clicked()), this, SLOT(selectTileRipPath()));
	QObject::connect(soundSaveSelectPath, SIGNAL(clicked()), this, SLOT(selectSoundRipPath()));
	
	// Connect player 1 pad redefine buttons.
	QObject::connect(changeP1UpButton, SIGNAL(clicked()), this, SLOT(redefineP1Up()));
	QObject::connect(changeP1DownButton, SIGNAL(clicked()), this, SLOT(redefineP1Down()));
	QObject::connect(changeP1LeftButton, SIGNAL(clicked()), this, SLOT(redefineP1Left()));
	QObject::connect(changeP1RightButton, SIGNAL(clicked()), this, SLOT(redefineP1Right()));
	QObject::connect(changeP1AButton, SIGNAL(clicked()), this, SLOT(redefineP1A()));
	QObject::connect(changeP1BButton, SIGNAL(clicked()), this, SLOT(redefineP1B()));
	
	// Connect player 2 pad redefine buttons.
	QObject::connect(changeP2UpButton, SIGNAL(clicked()), this, SLOT(redefineP2Up()));
	QObject::connect(changeP2DownButton, SIGNAL(clicked()), this, SLOT(redefineP2Down()));
	QObject::connect(changeP2LeftButton, SIGNAL(clicked()), this, SLOT(redefineP2Left()));
	QObject::connect(changeP2RightButton, SIGNAL(clicked()), this, SLOT(redefineP2Right()));
	QObject::connect(changeP2AButton, SIGNAL(clicked()), this, SLOT(redefineP2A()));
	QObject::connect(changeP2BButton, SIGNAL(clicked()), this, SLOT(redefineP2B()));	

	// Connect Pause/Start redefine buttons.
	QObject::connect(changeStartButton, SIGNAL(clicked()), this, SLOT(redefineStart()));
	QObject::connect(changePauseButton, SIGNAL(clicked()), this, SLOT(redefinePause()));
	
	// Connect save config button.
	QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveConfiguration()));	
	QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(applyConfiguration()));	
	
	// Connect Joystick 0 combobox to button assignations routines.
	QObject::connect(button1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button1Assigned(int)));	
	QObject::connect(button2ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button2Assigned(int)));	
	QObject::connect(button3ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button3Assigned(int)));	
	QObject::connect(button4ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button4Assigned(int)));	
	QObject::connect(button5ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button5Assigned(int)));	
	QObject::connect(button6ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button6Assigned(int)));	
	QObject::connect(button7ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button7Assigned(int)));	
	QObject::connect(button8ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(joy0Button8Assigned(int)));	
	
	// Queued connection for QLabel background color because joystick event come from a different thread.
	QObject::connect(this, SIGNAL(joyButton1Event(bool)), this, SLOT(joyButton1Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton2Event(bool)), this, SLOT(joyButton2Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton3Event(bool)), this, SLOT(joyButton3Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton4Event(bool)), this, SLOT(joyButton4Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton5Event(bool)), this, SLOT(joyButton5Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton6Event(bool)), this, SLOT(joyButton6Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton7Event(bool)), this, SLOT(joyButton7Changed(bool)), Qt::QueuedConnection);	
	QObject::connect(this, SIGNAL(joyButton8Event(bool)), this, SLOT(joyButton8Changed(bool)), Qt::QueuedConnection);	
}

/**
 * Update the QWidget with the values of the configuration.
 */
void QOsmoseConfiguration::synchronizeWithConfiguration()
{
	// Synchronize pathes.
	screenshotsPathLineEdit->setText(ocf->getScreenshotPath().c_str());  
	bbrPathLineEdit->setText(ocf->getBBRPath().c_str());
	saveStatePathLineEdit->setText(ocf->getSaveStatePath().c_str());
	tileSavePathLineEdit->setText(ocf->getTileCapturePath().c_str());
	soundSavePathLineEdit->setText(ocf->getSoundCapturePath().c_str());
	
	// Synchronize PAD1.
	p1UpLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, UP)));
	p1DownLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, DOWN)));
	p1LeftLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, LEFT)));
	p1RightLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, RIGHT)));
	p1ALabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, BUTTON_A)));
	p1BLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(0, BUTTON_B)));

	// Synchronize PAD2.
	p2UpLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, UP)));
	p2DownLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, DOWN)));
	p2LeftLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, LEFT)));
	p2RightLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, RIGHT)));
	p2ALabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, BUTTON_A)));
	p2BLabel->setText(KeyMapper::getKeyDescription(ocf->getPad(1, BUTTON_B)));	

	// Synchronize Start/Pause.
	pauseLabel->setText(KeyMapper::getKeyDescription(ocf->getPause()));
	startLabel->setText(KeyMapper::getKeyDescription(ocf->getStart()));
	
	// Synchronise Joystick0 button.
	button1ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(0)));
	button2ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(1)));
	button3ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(2)));
	button4ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(3)));
	button5ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(4)));
	button6ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(5)));
	button7ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(6)));
	button8ComboBox->setCurrentIndex(buttonAssignationToComboBox(ocf->getJoyButtonAssignation(7)));

	// Synchronize QLineEdit with joystick device.
	joystickDeviceQLineEdit->setText(QString(ocf->getJoystickDevice().c_str()));
}

/**
 * Convert given padKey  to joystick button combo box index.
 */
int QOsmoseConfiguration::buttonAssignationToComboBox(padKey k)
{	
	int ret;
	
	switch(k)
	{
		case START_GG: ret = 4; break;
		case PAUSE_NMI: ret = 3; break;
		case P1BUTTON_A: ret = 1; break;
		case P1BUTTON_B: ret = 2; break;
		default : ret = 0; break;		
	}
	
	return ret;
}

/**
 * Convert given combo box index to padKey.
 */
padKey QOsmoseConfiguration::comboBoxToButtonAssignation(int index)
{
	padKey ret;
	
	switch(index)
	{
		case 4: ret = START_GG; break;
		case 3: ret = PAUSE_NMI; break;
		case 1: ret = P1BUTTON_A; break;
		case 2: ret = P1BUTTON_B; break;
		default : ret = UNKNOWN; break;		
	}
	
	return ret;
}

/**
 * This slot is call when user clicks on save button.
 */
void QOsmoseConfiguration::saveConfiguration()
{
	try
	{
		ocf->setScreenshotPath(screenshotsPathLineEdit->text().toStdString());
		ocf->setSoundCapturePath(soundSavePathLineEdit->text().toStdString());
		ocf->setTileCapturePath(tileSavePathLineEdit->text().toStdString());
		ocf->setBBRPath(bbrPathLineEdit->text().toStdString());
		ocf->setSaveStatePath(saveStatePathLineEdit->text().toStdString());
		ocf->setJoystickDevice(joystickDeviceQLineEdit->text().toStdString());
		ocf->save();
		accept(); /* Call the accept slot. */
	}
	catch(string error)
	{
		QMessageBox::critical(this, "Configuration save failed", error.c_str());
	}
}


/**
 * This slot is call when user clicks on apply button.
 */
void QOsmoseConfiguration::applyConfiguration()
{
	ocf->setScreenshotPath(screenshotsPathLineEdit->text().toStdString());
	ocf->setSoundCapturePath(soundSavePathLineEdit->text().toStdString());
	ocf->setTileCapturePath(tileSavePathLineEdit->text().toStdString());
	ocf->setBBRPath(bbrPathLineEdit->text().toStdString());
	ocf->setSaveStatePath(saveStatePathLineEdit->text().toStdString());
	ocf->setJoystickDevice(joystickDeviceQLineEdit->text().toStdString());
	accept(); /* Call the accept slot. */
}


/**
 * This slot is call when user redefines joystick 0 button 1
 */
void QOsmoseConfiguration::joy0Button1Assigned(int v)
{
	ocf->assignJoyButton(0, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 2
 */
void QOsmoseConfiguration::joy0Button2Assigned(int v)
{
	ocf->assignJoyButton(1, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 3
 */
void QOsmoseConfiguration::joy0Button3Assigned(int v)
{
	ocf->assignJoyButton(2, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 4
 */
void QOsmoseConfiguration::joy0Button4Assigned(int v)
{
	ocf->assignJoyButton(3, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 5
 */
void QOsmoseConfiguration::joy0Button5Assigned(int v)
{
	ocf->assignJoyButton(4, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 6
 */
void QOsmoseConfiguration::joy0Button6Assigned(int v)
{
	ocf->assignJoyButton(5, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 7
 */
void QOsmoseConfiguration::joy0Button7Assigned(int v)
{
	ocf->assignJoyButton(6, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user redefines joystick 0 button 8
 */
void QOsmoseConfiguration::joy0Button8Assigned(int v)
{
	ocf->assignJoyButton(7, comboBoxToButtonAssignation(v));
}

/**
 * This slot is call when user clicks on Player 1 Up redefine button.
 */
void QOsmoseConfiguration::redefineP1Up()
{
	unsigned int the_key = pickupKey(p1UpLabel);
	ocf->setPad(0, UP, the_key);
}

/**
 * This slot is call when user clicks on Player 1 down redefine button.
 */
void QOsmoseConfiguration::redefineP1Down()
{
	unsigned int the_key = pickupKey(p1DownLabel);
	ocf->setPad(0, DOWN, the_key);
}

/**
 * This slot is call when user clicks on Player 1 Left redefine button.
 */
void QOsmoseConfiguration::redefineP1Left()
{
	unsigned int the_key = pickupKey(p1LeftLabel);
	ocf->setPad(0, LEFT, the_key);
}

/**
 * This slot is call when user clicks on Player 1 right redefine button.
 */
void QOsmoseConfiguration::redefineP1Right()
{
	unsigned int the_key = pickupKey(p1RightLabel);
	ocf->setPad(0, RIGHT, the_key);
}

/**
 * This slot is call when user clicks on Player 1 A redefine button.
 */
void QOsmoseConfiguration::redefineP1A()
{
	unsigned int the_key = pickupKey(p1ALabel);
	ocf->setPad(0, BUTTON_A, the_key);
}

/**
 * This slot is call when user clicks on Player 1 B redefine button.
 */
void QOsmoseConfiguration::redefineP1B()
{
	unsigned int the_key = pickupKey(p1BLabel);
	ocf->setPad(0, BUTTON_B, the_key);
}

/**
 * This slot is call when user clicks on Player 2 Up redefine button.
 */
void QOsmoseConfiguration::redefineP2Up()
{
	unsigned int the_key = pickupKey(p2UpLabel);
	ocf->setPad(1, UP, the_key);
}

/**
 * This slot is call when user clicks on Player 2 down redefine button.
 */
void QOsmoseConfiguration::redefineP2Down()
{
	unsigned int the_key = pickupKey(p2DownLabel);
	ocf->setPad(1, DOWN, the_key);
}

/**
 * This slot is call when user clicks on Player 2 Left redefine button.
 */
void QOsmoseConfiguration::redefineP2Left()
{
	unsigned int the_key = pickupKey(p2LeftLabel);
	ocf->setPad(1, LEFT, the_key);
}

/**
 * This slot is call when user clicks on Player 2 right redefine button.
 */
void QOsmoseConfiguration::redefineP2Right()
{
	unsigned int the_key = pickupKey(p2RightLabel);
	ocf->setPad(1, RIGHT, the_key);
}

/**
 * This slot is call when user clicks on Player 2 A redefine button.
 */
void QOsmoseConfiguration::redefineP2A()
{
	unsigned int the_key = pickupKey(p2ALabel);
	ocf->setPad(1, BUTTON_A, the_key);
}

/**
 * This slot is call when user clicks on Player 2 B redefine button.
 */
void QOsmoseConfiguration::redefineP2B()
{
	unsigned int the_key = pickupKey(p2BLabel);
	ocf->setPad(1, BUTTON_B, the_key);
}

/**
 * This slot is call when user clicks on Pause button.
 */
void QOsmoseConfiguration::redefinePause()
{
	unsigned int the_key = pickupKey(pauseLabel);
	ocf->setPause(the_key);
}

/**
 * This slot is call when user clicks on Start button.
 */
void QOsmoseConfiguration::redefineStart()
{
	unsigned int the_key = pickupKey(startLabel);
	ocf->setStart(the_key);
}


/**
 * It popups a dialog asking to hit the new key, then convert the key into an
 * ASCII description and update the given lQLabel.
 */
unsigned int QOsmoseConfiguration::pickupKey(QLabel *label)
{
	unsigned the_key;

	KeyGrabber * kg = new KeyGrabber(this);
	kg->exec();
	the_key = kg->getKeyPressed();
	label->setText(KeyMapper::getKeyDescription(the_key));
	delete kg;

	return the_key;
}

/**
 * KeyGrabber constructor.
 */
KeyGrabber::KeyGrabber(QWidget *parent) : QDialog(parent)
{
	setFixedSize(320, 200);
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	QLabel *label = new QLabel("Hit the new key");
	layout->addWidget(label);
	keyPressed = 0xFFFFFFFF;
}

/**
 * KeyGrabber keyPressedEvent callback, save the pressed key, and close
 * the QDialog.
 */
void KeyGrabber::keyPressEvent(QKeyEvent *evt)
{
	evt->accept();
	keyPressed = evt->key();
	//cout << keyPressed << endl;	
	setVisible(false);
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton1Changed(bool pressed)
{
	if (pressed == true)
	{
		button1QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button1QLabel->setStyleSheet("");
	}
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton2Changed(bool pressed)
{
	if (pressed == true)
	{
		button2QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button2QLabel->setStyleSheet("");
	}
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton3Changed(bool pressed)
{
	if (pressed == true)
	{
		button3QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button3QLabel->setStyleSheet("");
	}
}


/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton4Changed(bool pressed)
{
	if (pressed == true)
	{
		button4QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button4QLabel->setStyleSheet("");
	}
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton5Changed(bool pressed)
{
	if (pressed == true)
	{
		button5QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button5QLabel->setStyleSheet("");
	}
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton6Changed(bool pressed)
{
	if (pressed == true)
	{
		button6QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button6QLabel->setStyleSheet("");
	}
}

/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton7Changed(bool pressed)
{
	if (pressed == true)
	{
		button7QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button7QLabel->setStyleSheet("");
	}
}


/**
 *  This slot is called when a Joystick has been pressed or released.
 */
void QOsmoseConfiguration::joyButton8Changed(bool pressed)
{
	if (pressed == true)
	{
		button8QLabel->setStyleSheet("QLabel { background-color: rgb(192, 0, 0) }");
	}
	else
	{
		button8QLabel->setStyleSheet("");
	}
}

/* JoystickListener interface */
void QOsmoseConfiguration::buttonChanged(unsigned int button, bool pressed)
{
	QLabel *label;
	
	switch(button)
	{
		case 0:
			emit joyButton1Event(pressed);
		break;
		case 1:
			emit joyButton2Event(pressed);
		break;
		case 2:
			emit joyButton3Event(pressed);
		break;
		case 3:
			emit joyButton4Event(pressed);
		break;
		case 4:
			emit joyButton5Event(pressed);
		break;
		case 5:
			emit joyButton6Event(pressed);
		break;
		case 6:
			emit joyButton7Event(pressed);
		break;
		case 7:
			emit joyButton8Event(pressed);
		break;
	}
}

void QOsmoseConfiguration::xAxisChanged(int value)
{
}

void QOsmoseConfiguration::yAxisChanged(int value)
{
}

void QOsmoseConfiguration::joystickError()
{
}

