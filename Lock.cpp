#include <stdio.h>
#include <string>
#include "IllegalArgumentException.h"
#include "Lock.h"
using namespace std;

bool Lock::obtain(long lockWaitTimeout) throw (exception) {

	bool locked = obtain();
	if (lockWaitTimeout < 0 && lockWaitTimeout != LOCK_OBTAIN_WAIT_FOREVER)
		throw new IllegalArgumentException(LOCK_OBTAIN_WAIT_FOREVER);
	long maxSleepCount = lockWaitTimeout / LOCK_POLL_INTERVAL;
	long sleepCount = 0;
	while (!locked) {
		if (lockWaitTimeout != LOCK_OBTAIN_WAIT_FOREVER && sleepCount++ >= maxSleepCount) {
			//std::string reason = "Lock obtain timed out: " + this.toString();

			//LockObtainFailedException e = new LockObtainFailedException(reason);

			//throw e;
		}
		try {
			sleep(LOCK_POLL_INTERVAL);
		//} catch (InterruptedException ie) {
		} catch (...) {
			//throw new ThreadInterruptedException(ie);
		}
		locked = obtain();
	}
	return locked;
}
