#include <exception>
#include <stdio.h>
#include <iostream>
using namespace std;
class IllegalArgumentException:public exception{
private:
	long e_lockWaitTimeout;
public: 
	IllegalArgumentException(long lockWaitTimeout):exception()    
    {    
		e_lockWaitTimeout=lockWaitTimeout;
    } 
	const char*  what() const throw ()
    {
       const char* description ="lockWaitTimeout should be LOCK_OBTAIN_WAIT_FOREVER or a non-negative number got :%ld";
	   char  returndescription[1024];
	   snprintf(returndescription, sizeof(returndescription), description,e_lockWaitTimeout);
       return (const char*)returndescription;

    }
};
