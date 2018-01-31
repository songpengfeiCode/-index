#include <stdio.h>
#include <exception>
#include <set>
#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h>  
#include <string>  
#include <errno.h>

#include "mutex.h"

#include  "NativeFSLock.h"
using namespace std;

bool NativeFSLock::lockExists() {
	return lockexist;
}

set<string> NativeFSLock::LOCK_HELD =  set<string>();

NativeFSLock::NativeFSLock(string lockFilePath) {

	this->path      =  lockFilePath;
	lockexist       =  false;
}
	
bool NativeFSLock::obtain() throw (exception) {

	if (lockExists()) {
		return false;
	}
	printf("Found regular file: %s\n" , path.c_str());
	if(access(path.c_str(), F_OK) != 0) {
		throw new exception();
		//throw new exception("Found regular file where directory expected: %s" , path.c_str());
	}
	//string canonicalPath = path.getCanonicalPath();
	bool markedHeld = false;

	try {
		NativeFSLock_Mutex.Lock();
		{
			pos = LOCK_HELD.find(path);
			if (pos != LOCK_HELD.end()) {
				return false;
			} else {
			  LOCK_HELD.insert(path);
			  markedHeld = true;
			}
		}
        NativeFSLock_Mutex.Unlock();
		try {
			lockDirID = open(path.c_str(), O_RDWR);
		} 
		catch (exception e) {
		}
		//
		lock.l_whence  = SEEK_SET;  
		lock.l_start   = 0;  
		lock.l_len     = 0;  
		lock.l_type    = F_WRLCK;  
		lock.l_pid     = -1; 
		fcntl(lockDirID, F_SETLK, &lock);  
		if (lock.l_type != F_WRLCK)  
		{  
			printf("Write lock already set by %d .\n", lock.l_pid);  
		}  
		lockexist = true;

	} catch(...) {
		if (markedHeld && !lockExists()) {
			//synchronized
			NativeFSLock_Mutex.Lock();
			{
				pos = LOCK_HELD.find(path);
				if (pos != LOCK_HELD.end()) {
					LOCK_HELD.erase(path);
				}
				lockexist = false;
			}
			NativeFSLock_Mutex.Unlock();
		}
	}

	return lockexist;
}

	//synchronized 
void NativeFSLock::release() throw (exception) {
	if (lockExists()) {
	  try {
		    NativeFSLock_Mutex.Lock();
			lock.l_whence  = SEEK_SET;  
			lock.l_start   = 0;  
			lock.l_len     = 0;  
			lock.l_type    = F_UNLCK;  
			lock.l_pid     = -1; 
			fcntl(lockDirID, F_SETLK, &lock);  
			close(lockDirID);
			//synchronized(LOCK_HELD)
			pos = LOCK_HELD.find(path);
			if (pos != LOCK_HELD.end()) {
				LOCK_HELD.erase(path);
			}
			NativeFSLock_Mutex.Unlock();
			lockexist = false;
		} catch(...){
		}

	} else {
		bool obtained = false;
		try {
			if (!(obtained = obtain())) {
					//throw new LockReleaseFailedException(
					//"Cannot forcefully unlock a NativeFSLock which is held by another indexer component: "
					//+ path);
			}
		}catch(...){
		}
		if (obtained) {
		  release();
		}
	}
}

	//synchronized 
bool NativeFSLock::isLocked() throw (exception){

	if (lockExists()){
		return true;
	}else{
		return false;
	}
}

string NativeFSLock::toString() throw (exception){
	return "NativeFSLock@" + path;
}
