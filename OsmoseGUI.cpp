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
 * File : OsmoseGUI.cpp
 *
 * Description : This class is the main Application class. It contains
 * all QT objects and signal slots that are needed.
 *
 * Author : B.Vedder
 *
 * Date : Fri May 14 14:53:24 2010
 *
 */

#include "OsmoseGUI.h"

/**
 * Constructor.
 */
OsmoseGUI::OsmoseGUI(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	isFullscreen = false;
	rom_name = NULL;
	osmoseCore = NULL;
	saveStateSlot = 0;
	osmose_core_mutex = PTHREAD_MUTEX_INITIALIZER;

	QLogWindow::getInstance()->appendLog("Starting Osmose emulator.");
		
	/* Instanciate menus.*/
	QMenuBar *mb = menuBar();
	
	QMenu *menu = new QMenu("File");
	QAction *action = new QAction("&Open SMS/GG ROM", this);	
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_O));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(loadROM()));
	menu->addAction(action);

	action = new QAction("&Configure...", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(configure()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_C));
	menu->addAction(action);

	action = new QAction("&Log window ...", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(showLogWindow()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_L));
	menu->addAction(action);
	
	action = new QAction("E&xit Osmose", this);	
	//QObject::connect(action, SIGNAL(triggered()), qApp, SLOT(quit()));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(exitApplication()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_X));
	menu->addAction(action);
	
	
	mb->addMenu(menu);
	
	QGL::FormatOptions format = QGL::DirectRendering | QGL::DoubleBuffer | QGL::NoDepthBuffer | 
								QGL::NoAlphaChannel | QGL::NoAccumBuffer | QGL::NoStencilBuffer |
								QGL::NoStereoBuffers | QGL::NoOverlay | QGL::NoSampleBuffers;

	// Build OpenGL renderer widget.
	glImage = new QGLImage(this, 256, 192, format);
	setCentralWidget(glImage);	

	// Build emulation thread.
	//emuThread = new WhiteNoiseEmulationThread(glImage);
	emuThread = new WhiteNoiseEmulationThread(glImage);

	menu = new QMenu("Emulation");

	paused = false;
	pauseResume = new QAction("Pause", this);	
	QObject::connect(pauseResume, SIGNAL(triggered()), this, SLOT(pauseResumeEmulation()));
	menu->addAction(pauseResume);
	menu->addSeparator();

	action = new QAction("Save VDP &GFX", this);	
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_G));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(saveVDPGFX()));
	menu->addAction(action);
	
	
	action = new QAction("&Save screenshot", this);	
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_S));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(saveScreenshot()));
	menu->addAction(action);

	saveSoundQAction = new QAction("&Wave sound record", this);	
	saveSoundQAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_W));
	saveSoundQAction->setCheckable(true);
	saveSoundQAction->setChecked(false);
	QObject::connect(saveSoundQAction, SIGNAL(triggered()), this, SLOT(saveSound()));
	menu->addAction(saveSoundQAction);
	
	menu->addSeparator();

	action = new QAction("Hardware reset", this);	
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_R));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(resetEmulation()));
	menu->addAction(action);

	menu->addAction(action);
	mb->addMenu(menu);


	
	menu = new QMenu("Machine");
	mb->addMenu(menu);

	QActionGroup *timingGroup = new QActionGroup(this);
	ntscQAction = new QAction("NTSC Timing 60hz", this);
	QObject::connect(ntscQAction, SIGNAL(triggered()), this, SLOT(setNTSCTiming()));
	ntscQAction->setCheckable(true);
	ntscQAction->setChecked(true);
	menu->addAction(ntscQAction);
	timingGroup->addAction(ntscQAction);
	
	palQAction = new QAction("PAL Timing 50hz", this);
	QObject::connect(palQAction, SIGNAL(triggered()), this, SLOT(setPALTiming()));
	palQAction->setCheckable(true);
	palQAction->setChecked(false);
	menu->addAction(palQAction);
	timingGroup->addAction(palQAction);
	
	menu->addSeparator();
	
	QActionGroup *regionGroup = new QActionGroup(this);
	japaneseQAction = new QAction("Japanese machine", this);
	QObject::connect(japaneseQAction, SIGNAL(triggered()), this, SLOT(setJapanese()));
	japaneseQAction->setCheckable(true);
	japaneseQAction->setChecked(true);
	menu->addAction(japaneseQAction);
	regionGroup->addAction(japaneseQAction);
	
	europeanQAction = new QAction("European machine", this);
	QObject::connect(europeanQAction, SIGNAL(triggered()), this, SLOT(setEuropean()));
	europeanQAction->setCheckable(true);
	europeanQAction->setChecked(false);
	menu->addAction(europeanQAction);
	regionGroup->addAction(europeanQAction);
	mb->addMenu(menu);
	
	menu->addSeparator();
	irqHackQAction = new QAction("IRQ Hack (not recommended)", this);	
	QObject::connect(irqHackQAction, SIGNAL(triggered()), this, SLOT(toggleIrqHack()));
	irqHackQAction->setCheckable(true);
	irqHackQAction->setChecked(false);
	menu->addAction(irqHackQAction);
	menu->addSeparator();
	
	
	QActionGroup *mapperGroup = new QActionGroup(this);
	segaMapperQAction = new QAction("Default mapper", this);
	QObject::connect(segaMapperQAction, SIGNAL(triggered()), this, SLOT(setDefaultMapper()));
	segaMapperQAction->setCheckable(true);
	segaMapperQAction->setChecked(true);
	menu->addAction(segaMapperQAction);
	mapperGroup->addAction(segaMapperQAction);
	
	codemasterMapperQAction = new QAction("Codemaster mapper", this);
	QObject::connect(codemasterMapperQAction, SIGNAL(triggered()), this, SLOT(setCodeMasterMapper()));
	codemasterMapperQAction->setCheckable(true);
	codemasterMapperQAction->setChecked(false);
	menu->addAction(codemasterMapperQAction);
	mapperGroup->addAction(codemasterMapperQAction);
	mb->addMenu(menu);	

	koreanMapperQAction = new QAction("Koreand mapper", this);
	QObject::connect(koreanMapperQAction, SIGNAL(triggered()), this, SLOT(setKoreanMapper()));
	koreanMapperQAction->setCheckable(true);
	koreanMapperQAction->setChecked(false);
	menu->addAction(koreanMapperQAction);
	mapperGroup->addAction(koreanMapperQAction);
	mb->addMenu(menu);
	
	/* Create video filtering checkable group. */
	menu = new QMenu("Video");
	QActionGroup *filteringGroup = new QActionGroup(this);
	filteringGroup->setExclusive(true);	// Bilinear OR Nearest neighboor.
	
	action = new QAction("&Bilinear filtering", this);
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_B));	
	QObject::connect(action, SIGNAL(triggered()), glImage, SLOT(bilinearFilteringOn()));
	action->setCheckable(true);
	action->setChecked(false);
	menu->addAction(action);
	filteringGroup->addAction(action);

	action = new QAction("&Nearest neighboor filtering", this);	
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_N));
	QObject::connect(action, SIGNAL(triggered()), glImage, SLOT(nearestNeighboorFilteringOn()));
	action->setCheckable(true);
	action->setChecked(true);
	menu->addAction(action);
	filteringGroup->addAction(action);

	menu->addSeparator();


	QActionGroup *videoSizeGroup = new QActionGroup(this);
	action = new QAction("Original size (256x192)", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(sizeX1()));
	action->setCheckable(true);
	action->setChecked(false);
	menu->addAction(action);
	videoSizeGroup->addAction(action);
	
	action = new QAction("Size x2 (512x384)", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(sizeX2()));
	action->setCheckable(true);
	action->setChecked(true);
	menu->addAction(action);
	videoSizeGroup->addAction(action);
	
	action = new QAction("Size x3 (768x576)", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(sizeX3()));
	action->setCheckable(true);
	action->setCheckable(true);
	action->setChecked(false);
	menu->addAction(action);
	videoSizeGroup->addAction(action);
	
	action = new QAction("Size x4 (1024x768)", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(sizeX4()));
	action->setCheckable(true);
	action->setChecked(false);
	menu->addAction(action);
	videoSizeGroup->addAction(action);
	
	action = new QAction("Size x5 (1280x860)", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(sizeX5()));
	action->setCheckable(true);
	action->setChecked(false);
	menu->addAction(action);
	videoSizeGroup->addAction(action);
	menu->addSeparator();
	
	action = new QAction("Fullscreen", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(fullscreen()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_F));
	menu->addAction(action);
	
	mb->addMenu(menu);

	// SAVES Menu

	
	menu = new QMenu("Saves");
	action = new QAction("Save machine state", this);	
	action->setShortcut( QKeySequence(Qt::Key_F11));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(saveState()));
	menu->addAction(action);
	
	action = new QAction("Load machine state", this);	
	action->setShortcut( QKeySequence(Qt::Key_F12));
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(loadState()));
	menu->addAction(action);	
	
	menu->addSeparator();
	
	/* Save state slot selection. */
	QActionGroup *selectSlotGroup = new QActionGroup(this);
	selectSlotGroup->setExclusive(true); // Only one slot selected at a time.
	action = new QAction("Select slot 1", this);
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(selectSlot0()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_1));	
	action->setCheckable(true);
	action->setChecked(true);
	selectSlotGroup->addAction(action);
	menu->addAction(action);
	
	action = new QAction("Select slot 2", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(selectSlot1()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_2));
	action->setCheckable(true);
	action->setChecked(false);
	selectSlotGroup->addAction(action);
	menu->addAction(action);
	
	action = new QAction("Select slot 3", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(selectSlot2()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_3));
	action->setCheckable(true);
	action->setChecked(false);
	selectSlotGroup->addAction(action);
	menu->addAction(action);
	
	action = new QAction("Select slot 4", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(selectSlot3()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_4));
	action->setCheckable(true);
	action->setChecked(false);
	selectSlotGroup->addAction(action);	
	menu->addAction(action);
	
	action = new QAction("Select slot 5", this);	
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(selectSlot4()));
	action->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_5));
	action->setCheckable(true);
	action->setChecked(false);
	selectSlotGroup->addAction(action);
	menu->addAction(action);	
	
	mb->addMenu(menu);
	
	// Instanciate Configuration object.
	configuration = new OsmoseConfigurationFile();
	// Try to load configuration file.
	try
	{
		configuration->load();
	}
	catch(string error)
	{
		// Unable to load or create configuration file. Display a message.
		error = error + "\nCreating default configuration in user's directory.\nPlease configure path or you will save everything in your home directory !";
		QMessageBox::critical(this, "No configuration file found", error.c_str());

		// Unable to load configuration file, try to create a new one.
		try
		{
			configuration->createDefautConfigurationFile();
		}
		catch(string error)
		{
			// Unable to load or create configuration file. Display a message.
			QMessageBox::critical(this, "Unable to create default Configuration file", error.c_str());
		}
	}
	
	/* Try to find a Joystick*/
	js0 = NULL;
	try
	{
		js0 = new Joystick((char *)configuration->getJoystickDevice().c_str(), this);
		string msg = "Found Joystick :";
		msg = msg + js0->getStrID();		
		QLogWindow::getInstance()->appendLog(msg);
	}
	catch(string &err)
	{
		js0 = NULL;
		string msg = "No joystick found (device : ";
		msg = msg + configuration->getJoystickDevice();
		msg = msg + ").";
		QLogWindow::getInstance()->appendLog(msg);
	}
	
	// Enable Drop events.
	setAcceptDrops(true);	
	
	// Start emulation thread. It does not means that emulation is started !
	emuThread->start();	
	emuThread->startEmulation();
}

/**
 * Destructor.
 */
OsmoseGUI::~OsmoseGUI()
{
}

void OsmoseGUI::configure()
{
	QOsmoseConfiguration *configWindow;

	if (js0 == NULL)
	{
		configWindow = new QOsmoseConfiguration(configuration, "No joystick found", this);
	}
	else
	{
		configWindow = new QOsmoseConfiguration(configuration, js0->getStrID(), this);
		js0->setListener(configWindow);
	}
	configWindow->exec();
	if (js0 != NULL) js0->setListener(this);
}

void OsmoseGUI::sizeX1()
{
	resize(256, 192 + MENU_HEIGHT);
	string msg = "Video set to original size (256x192).";		
	QLogWindow::getInstance()->appendLog(msg);	
}
 
/**
 * Resize X2 slot.
 * Resize the main window to new size.
 */
void OsmoseGUI::sizeX2()
{
	resize(512, 384 + MENU_HEIGHT);
	string msg = "Video set to original size x2 (512x384).";		
	QLogWindow::getInstance()->appendLog(msg);	
}
 
/**
 * Resize X3 slot.
 * Resize the main window to new size.
 */
void OsmoseGUI::sizeX3()
{
	resize(768, 576 + MENU_HEIGHT);
	string msg = "Video set to original size x3 (768x576).";		
	QLogWindow::getInstance()->appendLog(msg);	
}

/**
 * Resize X4 slot.
 * Resize the main window to new size.
 */ 
void OsmoseGUI::sizeX4()
{
	resize(1024, 768 + MENU_HEIGHT);
	string msg = "Video set to original size x4 (1024x768).";		
	QLogWindow::getInstance()->appendLog(msg);	
}

/**
 * Resize X5 slot.
 * Resize the main window to new size.
 */
void OsmoseGUI::sizeX5()
{
	resize(1280, 860 + MENU_HEIGHT);
	string msg = "Video set to original size x5 (1280x860).";		
	QLogWindow::getInstance()->appendLog(msg);
}

/**
 * Fullscreen toggle.
 */
void OsmoseGUI::fullscreen()
{
	isFullscreen ^= 1;
	
	if (isFullscreen)
	{
		showFullScreen();
		// Now do this on QLImage to hide menus.
		string msg = "Video mode set to fullscreen.";		
		QLogWindow::getInstance()->appendLog(msg);
	}
	else
	{
		showNormal();
		string msg = "Video mode set to windowed.";		
		QLogWindow::getInstance()->appendLog(msg);
	}
}

/**
 * loadROM (menu) slot.
 */
void OsmoseGUI::loadROM()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load File", "./", "SMS/GG Roms (*.zip *.sms *.gg)");
	if (!filename.isEmpty()) 
	{
		loadTheROM(filename);
	}
}

/**
 * This method will load a ROM, instanciate emulator core and start it.
 * It also disconnect and reconnect emuThread QObject signals/slots. 
 */
void OsmoseGUI::loadTheROM(QString filename)
{
	if (rom_name != NULL) delete rom_name;
	//rom_name = qstrdup(qPrintable(filename));
	rom_name = qstrdup( (const char *)filename.toStdString().c_str() );
	
	try
	{
		// Stop and kill previous thread.
		emuThread->abortEmulation();
		bool killed = emuThread->wait(1000); // Wait for thread end for 1 second.
		if (!killed) 
		{
			string msg = "Warning : could not kill emulation thread !";		
			QLogWindow::getInstance()->appendLog(msg);
		}
		delete emuThread;

		
		// Stop recording sound if needed.
		saveSoundQAction->setChecked(false);
		
		QLogWindow::getInstance()->addSeparator();
		QLogWindow::getInstance()->appendLog("Trying to load new ROM.");	
		
		
		// Build new Emulation thread.
		OsmoseEmulationThread *osm = new OsmoseEmulationThread(glImage, rom_name, configuration, &osmose_core_mutex);
		emuThread = osm;
		emuThread->start();	
		emuThread->startEmulation();
		QLogWindow::getInstance()->appendLog("Starting emulation !");	
		osmoseCore = osm->getCore(); // Tmp is OsmoseEmuThread, not just EmuThread !
		
		// Disconnect / reconnect pause SLOT.
		QObject::disconnect(pauseResume, SIGNAL(triggered()), this, SLOT(pauseResumeEmulation()));		
		QObject::connect(pauseResume, SIGNAL(triggered()), this, SLOT(pauseResumeEmulation()));
		paused = false;
		pauseResume->setText("Pause");		

		updateMachineMenu();
	}
	catch(string error_msg)
	{
		// An exception occurs while creation OsmoseEmulationCore. Launch
		// White noise animation instead.
		emuThread = new WhiteNoiseEmulationThread(glImage);
		emuThread->start();
		emuThread->startEmulation();
		
		QLogWindow::getInstance()->appendLog(error_msg);
		QString msg(error_msg.c_str());
		QMessageBox::critical(this, "Oops, we get an error", msg);
	}	
}


/**
 * pauseResumeEmulation (menu) slot.
 * This slot is called when emulation is asked for pause and resume. It
 * is responsible for toggle action label from Pause to Resume.
 */
void OsmoseGUI::pauseResumeEmulation()
{
	if (!paused)
	{
		pauseResume->setText("Resume");
		emuThread->pauseEmulation();
		paused = true;
		string msg = "Emulation paused.";
		QLogWindow::getInstance()->appendLog(msg);
	}
	else
	{
		pauseResume->setText("Pause");
		emuThread->startEmulation();
		paused = false;
		string msg = "Emulation resumed.";
		QLogWindow::getInstance()->appendLog(msg);
	}
}

/**
 * resetEmulation (menu) slot.
 * This slot is called when emulation is asked for Reset.
 */
void OsmoseGUI::resetEmulation()
{
		emuThread->resetEmulation();
		pauseResume->setText("Pause");
		emuThread->startEmulation();
		paused = false;
		
		string msg = "Hardware reset.";
		QLogWindow::getInstance()->appendLog(msg);
}

/**
 */
void OsmoseGUI::keyPressEvent(QKeyEvent *event)
{
	event->accept();  // Event is comsumed by our handler.
	if (!event->isAutoRepeat())
	{
		padKey k = configuration->keyToKeyPad(event->key());
		if (k != UNKNOWN) emuThread->keyPressed(k);
	}
}

/**
 */
void OsmoseGUI::keyReleaseEvent(QKeyEvent *event)
{
	event->accept(); // Event is comsumed by our handler.
	if (!event->isAutoRepeat())
	{
		padKey k = configuration->keyToKeyPad(event->key());
		if (k != UNKNOWN) emuThread->keyReleased(k);	
	}
}

/**
 */
void OsmoseGUI::saveScreenshot()
{
	// Simulate a fake 'screenshot' key.
	emuThread->keyPressed(SCREENSHOT);
}

/**
 */
void OsmoseGUI::saveSound()
{
	if (osmoseCore == NULL) return;
	
	// Simulate a fake 'save wave sound' key.
	emuThread->keyPressed(SOUNDSHOT);
	if (saveSoundQAction->isChecked())
	{
		// Save sound has just been selected.
		bool success = osmoseCore->startRecordingSounds();
		if (!success)
		{
			// Unable to save wav file.
			saveSoundQAction->setChecked(false);
		}
	}
	else
	{
		// Stop sound recording has just been selected.
		osmoseCore->stopRecordingSounds();
	}
}

/**
 * Select the save/load state slot.
 */
void OsmoseGUI::selectSlot0()
{
	saveStateSlot = 0;
}

/**
 * Select the save/load state slot.
 */
void OsmoseGUI::selectSlot1()
{
	saveStateSlot = 1;
}

/**
 * Select the save/load state slot.
 */
void OsmoseGUI::selectSlot2()
{
	saveStateSlot = 2;
}

/**
 * Select the save/load state slot.
 */
void OsmoseGUI::selectSlot3()
{
	saveStateSlot = 3;
}

/**
 * Select the save/load state slot.
 */
void OsmoseGUI::selectSlot4()
{
	saveStateSlot = 4;
}
/**
 */
void OsmoseGUI::saveState()
{
	if (osmoseCore == NULL) return;
	bool success = osmoseCore->saveSaveState(saveStateSlot);
}

/**
 */
void OsmoseGUI::loadState()
{
	if (osmoseCore == NULL) return;
	bool success = osmoseCore->loadSaveState(saveStateSlot);
}

/**
 */
void OsmoseGUI::exitApplication()
{
	emuThread->abortEmulation();
	bool killed = emuThread->wait(1000); // Wait for thread end for 1 second.
	if (!killed) cerr << "Warning : could not kill emulation thread !" << endl;
	delete emuThread;
	qApp->quit();
}

/**
 * This method overrides the default closeEvent handler.
 */
void OsmoseGUI::closeEvent(QCloseEvent * )
{
	exitApplication();
}


/**
 */
void OsmoseGUI::saveVDPGFX()
{
	if (osmoseCore == NULL) return;
	bool success = osmoseCore->captureTiles();
}

/**
 */
void OsmoseGUI::setDefaultMapper()
{
	if (osmoseCore == NULL) return;
	osmoseCore->forceMemoryMapper(SegaMapper);
	osmoseCore->reset();
	string msg = "Forced Sega mapper, then hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);
	
}

/**
 */
void OsmoseGUI::setCodeMasterMapper()
{
	if (osmoseCore == NULL) return;
	osmoseCore->forceMemoryMapper(CodemasterMapper);
	osmoseCore->reset();
	string msg = "Forced Codemaster mapper, then hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);
}

/**
 */
void OsmoseGUI::setKoreanMapper()
{
	if (osmoseCore == NULL) return;
	osmoseCore->forceMemoryMapper(KoreanMapper);
	osmoseCore->reset();
	string msg = "Forced Korean mapper, then hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);
}

/**
 */
void OsmoseGUI::setNTSCTiming()
{
	if (osmoseCore == NULL) return;
	osmoseCore->forceNTSCTiming(true);
	string msg = "Forced NTSC timing, no hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);
}

/**
 */
void OsmoseGUI::setPALTiming()
{
	if (osmoseCore == NULL) return;
	osmoseCore->forceNTSCTiming(false);
	string msg = "Forced PAL timing, no hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);	
}

/**
 */
void OsmoseGUI::setJapanese()
{
	if (osmoseCore == NULL) return;
	opt.WorldVersion = false;
	string msg = "Forced Japanese hardware, no hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);	
}

/**
 */
void OsmoseGUI::setEuropean()
{
	if (osmoseCore == NULL) return;
	opt.WorldVersion = true;
	string msg = "Forced European hardware, no hardware reset.";
	QLogWindow::getInstance()->appendLog(msg);
}

/**
 * Loading a rom sometimes changes Osmose's option e.g.
 * Codemaster mapper required for some games.  This method 
 * synchronize opt structure and Machine menu.
 */
void OsmoseGUI::updateMachineMenu()
{
	if (opt.WorldVersion == true)
	{
		europeanQAction->setChecked(true);
	}
	else
	{
		japaneseQAction->setChecked(true);
	}
	
	if (opt.ntsc == true)
	{
		ntscQAction->setChecked(true);
	}
	else
	{	
		palQAction->setChecked(true);
	}	
	
	if (opt.irq_hack == true)
	{
		irqHackQAction->setChecked(true);
	}
	else
	{	
		irqHackQAction->setChecked(false);
	}		
	
	switch(opt.mapperType)
	{
		case SegaMapper:
			segaMapperQAction->setChecked(true);
		break;
		case CodemasterMapper:
			codemasterMapperQAction->setChecked(true);
		break;		
		case KoreanMapper:
			koreanMapperQAction->setChecked(true);
		break;
	}
}

/**
 * This method toggles IRQ Hack.
 */
void OsmoseGUI::toggleIrqHack()
{
	if (irqHackQAction->isChecked())
	{
		opt.irq_hack = true;
		string msg = "IRQ hack turned ON.";
		QLogWindow::getInstance()->appendLog(msg);
	}
	else
	{
		opt.irq_hack = false;
		string msg = "IRQ hack turned OFF.";
		QLogWindow::getInstance()->appendLog(msg);
	}
}


void OsmoseGUI::showLogWindow()
{
	QLogWindow::getInstance()->setVisible(true);
}

/* JoystickListener interface */
void OsmoseGUI::buttonChanged(unsigned int button, bool pressed)
{
    if (osmoseCore == NULL) return;
	
	padKey b = configuration->getJoyButtonAssignation(button);
	switch(b)
	{
		case P1BUTTON_A:
			osmoseCore->P1AButtonChanged(pressed);
		break;
		
		case P1BUTTON_B:
			osmoseCore->P1BButtonChanged(pressed);
		break;
		
		case PAUSE_NMI:
			osmoseCore->PauseButtonChanged(pressed);
		break;

		case START_GG:
			osmoseCore->StartButtonChanged(pressed);
		break;

		default:
		break;
	}
}

void OsmoseGUI::xAxisChanged(int value)
{
	if (osmoseCore == NULL) return;
	if (value == 0)
	{
		osmoseCore->P1RightChanged(false);
		osmoseCore->P1LeftChanged(false);
	}
	
	if (value > 0)
	{
		osmoseCore->P1RightChanged(true);
		osmoseCore->P1LeftChanged(false);	
	}
	
	if (value < 0)
	{
		osmoseCore->P1RightChanged(false);
		osmoseCore->P1LeftChanged(true);
	}
}

void OsmoseGUI::yAxisChanged(int value)
{
	if (osmoseCore == NULL) return;
	if (value == 0)
	{
		osmoseCore->P1UpChanged(false);
		osmoseCore->P1DownChanged(false);
	}
	
	if (value > 0)
	{
		osmoseCore->P1UpChanged(false);
		osmoseCore->P1DownChanged(true);
	}
	
	if (value < 0)
	{
		osmoseCore->P1UpChanged(true);
		osmoseCore->P1DownChanged(false);
	}
}

void OsmoseGUI::joystickError()
{
}


void OsmoseGUI::dropEvent(QDropEvent *event)
{
	QString fileDroped; 
	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> urls = event->mimeData()->urls();
		fileDroped = urls.at(0).toString();
		fileDroped.replace("file://", "");
		loadTheROM(fileDroped);
	}
}


/*
	On ubuntu 10.04 Drop formats received are :
	x-special/gnome-icon-list
	text/uri-list
	UTF8_STRING
	text/plain
	COMPOUND_TEXT
	TEXT
	STRING
	text/plain;charset=utf-8
*/
void OsmoseGUI::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls())
	{
		event->accept();
	}
}

