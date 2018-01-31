#ifndef __NATIVELOCK_H__
#define __NATIVELOCK_H__
#include <sys/types.h>
#include <stdio.h>
#include <exception>
#include <set> 
#include <unistd.h>  
#include <string> 
#include <fcntl.h> 

#include  "Lock.h"
#include  "mutex.h"
using namespace std;
using  namespace __gnu_cxx; 

class NativeFSLock : public Lock {

private:
  	struct flock                lock;
  	int                         lockDirID ;
 	string                      path;
	set<string>::iterator       pos; 
	bool                        lockexist;
	LUCENE_Mutex                NativeFSLock_Mutex;
public:	
	static set<string>  LOCK_HELD;// = new set<string>();
    //用hash_set
    
	
private:
	//synchronized
	bool lockExists();

public:
    NativeFSLock(string lockFilePath);
	
    bool obtain() throw (exception);

	//synchronized 
	void release() throw (exception);

	//synchronized 
	bool isLocked() throw (exception);

	string toString() throw (exception);
};
//set<string> NativeFSLock::LOCK_HELD =  set<string>();
#endif