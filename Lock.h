
#ifndef __LOCK_H__
#define __LOCK_H__
#include <stdio.h>
#include <string>
//#include "IllegalArgumentException.h"
using namespace std;

class Lock{
public:
    //long LOCK_POLL_INTERVAL = 1000;
	//long LOCK_OBTAIN_WAIT_FOREVER = -1;
	long LOCK_POLL_INTERVAL;
	long LOCK_OBTAIN_WAIT_FOREVER;
public:
    bool obtain(long lockWaitTimeout) throw (exception);
    Lock():LOCK_POLL_INTERVAL(1000),LOCK_OBTAIN_WAIT_FOREVER(-1)
	{
	}
public:
	virtual void release() throw (exception)  = 0 ;

	virtual bool isLocked()throw (exception) = 0 ;
	
	virtual bool obtain()throw (exception) = 0   ;

};
#endif
