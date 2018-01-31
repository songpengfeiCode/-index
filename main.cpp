#include <iostream>
#include <unistd.h>
#include <string>

#include "Lock.h"
#include "NativeFSLock.h"
#include "FSLockFactory.h"
#include "NativeFSLockFactory.h"



using namespace std;

int main(int argc, char **argv)
{
	bool exitflag = false;
	FSLockFactory* instant = new NativeFSLockFactory();
	Lock*          mLock   = instant->makeLock("/home/spf/1.lock");
	Lock*          mLock1   = instant->makeLock("/home/spf/1.lock");
	printf("--------------test begin!--------------\n");
	if(mLock->obtain())
	{
		printf("OK!\n");
	}
	else
	{
        printf("Faild\n");
	}
		if(mLock1->obtain())
	{
		printf("OK!\n");
	}
	else
	{
        printf("Faild\n");
	}
	if(mLock->isLocked())
	{
		printf("isLocked!\n");
	}
	else
	{
    printf("noLocked\n");
	}
	mLock->release();
	if(mLock->isLocked())
	{
		printf("isLocked!\n");
	}
	else
	{
        printf("noLocked\n");
	}
	if(mLock->obtain())
	{
		printf("OK!\n");
	}
	else
	{
        printf("Faild\n");
	}
	printf("--------------test end!--------------\n");
}
