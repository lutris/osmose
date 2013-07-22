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
 * File : Pthreadcpp.cpp
 *
 * Description :
 *
 * Author : B.Vedder
 *
 * Date : Fri Dec 17 07:44:27 2010
 *
 */

#include "Pthreadcpp.h"

/**	
 * Description : This class is the most basic pthread C++ encapsulation.
 * It's used to handle JOINABLE / UNDETACHED posix threads.
 * To create a thread, simply inherit this class, and override the run()
 * method, and call the start method with input argument if any. Finally
 * call Join(...) to wait the Thread if needed.
 *
 * Author : B.Vedder
 *
 * Date : Wed Dec 15 15:44:04 2010
 *
 */


/**
 * Constructor.
 */
Thread::Thread()
{
	// The posix thread has not been created yet.
	_created = false;
	_joined  = false;
}


/**
 * Destructor.
 */
Thread::~Thread()
{  
    /*	
		Posix pthread_join() says :
		When  a	joinable  thread  terminates,  its  memory  resources  (thread
		descriptor and stack) are not deallocated until another thread performs
		pthread_join on it. Therefore, pthread_join must  be  called  once  for
		each joinable thread created to avoid memory leaks.
    */
	if ((_created == true) && (_joined == false))
	{
		pthread_join(_thread, NULL);
	}
}

/**
 * Start, by entering the Thread main loop. The created thread is JOINABLE.
 * Default value of param is NULL.
 * Returned value is pthread_create(...) return value.
 */
int Thread::start(void *param)
{
	_inputArg = param;
	int retValue = pthread_create(&_thread, NULL, Thread::entryPoint, (void *)this);
	_created = (retValue == 0) ? true : false;
	return retValue;
}

/**
 * This static method is here because pthread_create cannot take member function
 * as start_routine, except if it's static. So we made a private static that can
 * only be called by non static member start(). EntryPoint method recieved a this
 * pointer, and use it to call the runnable run() method.
 */
void *Thread::entryPoint(void *instance)
{
	Thread *myself = (Thread *)instance;
	myself->run( myself->getArg());
}

/**
 * Wait for termination of this thread. If retVal is not NULL, the value returned
 * by the thread will be stored in the location pointed to by thread_return.
 * On success, zero is returned, else the error code given by pthread_join.
 */
int Thread::join(void **thread_return)
{
	if (_created != true) return ESRCH; /* Not started again. */
	_joined = true;
	return pthread_join(_thread, thread_return);
}
