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
 * File : OsmoseGUI.h
 *
 * Description : This class is the main Application class. It contains
 * all QT objects and signal slots that are needed.
 *
 * Author : B.Vedder
 *
 * Date : Fri May 14 14:53:24 2010
 *
 */

#ifndef OSMOSE_GUI_H
#define OSMOSE_GUI_H

#include <pthread.h>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include "QGLImage.h"
#include "OsmoseEmulationThread.h"
#include "WhiteNoiseEmulationThread.h"
#include "QOsmoseConfiguration.h"
#include "OsmoseConfigurationFile.h"
#include "OsmoseCore.h"
#include "MemoryMapper.h"
#include "QLogWindow.h"
#include "Joystick.h"

#define MENU_HEIGHT	20

class OsmoseGUI : public QMainWindow, JoystickListener
{
	Q_OBJECT;
	
public:
	OsmoseGUI(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~OsmoseGUI();
	
	/* JoystickListener interface */
	void buttonChanged(unsigned int button, bool pressed); /* True when pressed */
    void xAxisChanged(int value);
	void yAxisChanged(int value);
	void joystickError();

protected:
	void closeEvent(QCloseEvent * );	
	void dropEvent(QDropEvent *e);
	void dragEnterEvent(QDragEnterEvent *event);
	
protected slots:
	void sizeX1(); 
	void sizeX2(); 
	void sizeX3(); 
	void sizeX4(); 
	void sizeX5();
	void fullscreen();
	void loadROM();
	void pauseResumeEmulation();
	void resetEmulation();
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void configure();
	void saveScreenshot();
	void saveSound();
	void saveState();
	void saveVDPGFX();
	void loadState();
	void selectSlot0();
	void selectSlot1();
	void selectSlot2();
	void selectSlot3();
	void selectSlot4();
	void exitApplication();

	void setDefaultMapper();
	void setCodeMasterMapper();
	void setKoreanMapper();
	void setNTSCTiming();
	void setPALTiming();
	void setJapanese();
	void setEuropean();
	void toggleIrqHack();
	void showLogWindow();
	
private:
	bool paused;
	QGLImage *glImage;
	EmulationThread *emuThread;
	char *rom_name;
	QAction *pauseResume;
	QAction *saveSoundQAction;
	QAction *ntscQAction;
	QAction *palQAction;
	QAction *japaneseQAction;
	QAction *europeanQAction;	
	QAction *codemasterMapperQAction;
	QAction *segaMapperQAction;
	QAction *koreanMapperQAction;
	QAction *irqHackQAction;
	
	OsmoseConfigurationFile *configuration;
	OsmoseCore *osmoseCore;	
	int saveStateSlot;
	pthread_mutex_t osmose_core_mutex;	// OsmoseCore access mutex.
	
	void updateMachineMenu();
	void loadTheROM(QString name);
	bool isFullscreen;
	Joystick *js0;
};

#endif	// OsmoseGUI
