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
 * File : Pthreadcpp.h
 *
 * Description : This class provide basic Mutex and Thread C++ encapsulation.
 *
 * Author : B.Vedder
 *
 * Date : Fri Dec 17 07:44:27 2010
 *
 */

#ifndef PTHREADCPP_H
#define PTHREADCPP_H

#include <pthread.h>
#include <errno.h>


/**
 * Tiny utility class to benefit from C++ auto destruction of objects.
 * Creating a LOCAL Mutex object will lock the mutex. Leaving the method
 * will destroy the object automatically and free the mutex. So in order
 * to get a method thread safe, simply add at the begining :
 * MutexLocker(the_mutex);
 */
class MutexLocker
{
	public:
		MutexLocker(pthread_mutex_t *mutex) {the_mutex = mutex; pthread_mutex_lock(the_mutex); }
		~MutexLocker() {pthread_mutex_unlock(the_mutex);}

	private:
		pthread_mutex_t *the_mutex;
};




/**	
 *
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

class Thread
{
public:
   
	Thread();
    int start(void *param = NULL);
	int join(void **retVal);
	virtual ~Thread();  
	
protected:
	
	virtual void* run(void *p) = 0;	/* Override this with your own. */
	
private:
	
	bool _created;
	bool _joined;
	pthread_t _thread;
	void *_inputArg;
	void *getArg() {return _inputArg;}
	static void *entryPoint(void *);
};




#endif	// PTHREADCPP_H
