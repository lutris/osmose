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
 * File : QLogWindow.h
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Sun Dec 12 08:33:30 2010
 *
 */

#ifndef QLOGWINDOW_H
#define QLOGWINDOW_H

#include <iostream>
#include <QTime>
#include "ui_LogWindow.h"

using namespace std;

class QLogWindow : public QWidget, private Ui::LogWindow
{

Q_OBJECT

public:
	~QLogWindow();
	static QLogWindow *getInstance(QWidget *parent = 0);
	void appendLog(string &);
	void appendLog(char *);
	void addSeparator();

protected slots:
	void hideWindow();
	void clearLogs();

protected:

private:
	static QLogWindow *self;
	QLogWindow(QWidget *parent = 0);
	QString getTimePrefix();

};

#endif	// QLOGWINDOW_H
