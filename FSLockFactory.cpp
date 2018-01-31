#include <sys/file.h>
#include <stdio.h>
#include <exception>

#include "FSLockFactory.h"
using namespace std;

void  FSLockFactory::setLockPrefix(std::string lockPrefix){
	this->lockPrefix = lockPrefix;
}

std::string  FSLockFactory::getLockPrefix(){
	return this->lockPrefix;
}

//FILE*  FSLockFactory::getLockDir() {
//	return lockDir;
//}
