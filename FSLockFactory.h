#ifndef __FSLOCKFACTORY_H__
#define __FSLOCKFACTORY_H__

#include <sys/file.h>
#include <stdio.h>
#include <exception>
#include <string>
#include "Lock.h"

using namespace std;
class FSLockFactory {
protected:
 	std::string  lockPrefix;
public:
    void  setLockPrefix(std::string lockPrefix);
    std::string  getLockPrefix();
    //FILE*  getLockDir();

    virtual  Lock*  makeLock(std::string lockName) = 0;
	virtual  void  clearLock(std::string lockName) throw (std::exception)  = 0 ;
};
#endif