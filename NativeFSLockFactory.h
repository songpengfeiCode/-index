#ifndef __NATIVEFSLOCKFACTORY_H__
#define __NATIVEFSLOCKFACTORY_H__

#include <stdio.h>
#include <exception>
#include <set>
#include <fcntl.h>  
#include <unistd.h>  
#include <string>  
#include <errno.h>

#include  "FSLockFactory.h"
#include  "Lock.h"
using namespace std;

class NativeFSLockFactory : public FSLockFactory {
public: 
	NativeFSLockFactory(){
		
	}
  	Lock* makeLock(std::string lockName);  
  	void clearLock(std::string lockName) throw (exception);
};
#endif
