#include <stdio.h>
#include <exception>
#include <hash_set> 
#include <fcntl.h>  
#include <unistd.h>  
#include <string>  
#include <errno.h>

#include  "FSLockFactory.h"
#include  "Lock.h"
#include  "NativeFSLock.h"
#include  "NativeFSLockFactory.h"
using namespace std;

Lock* NativeFSLockFactory::makeLock(std::string lockName) {
	if (lockPrefix.c_str() != "")
		lockName = lockPrefix  + lockName;
	return new NativeFSLock(lockName);
}

void NativeFSLockFactory::clearLock(std::string lockName) throw (exception) {
	/*
	if(lockDir != NULL){
		makeLock(lockName).release();
		if (lockPrefix != NULL) {
			lockName = lockPrefix + "-" + lockName;
		}
		lockDir.close();
	}
	*/
}
