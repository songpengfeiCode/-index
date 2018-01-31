#ifndef MUTEX_H_
#define MUTEX_H_

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include "typedef.h"

class LUCENE_Mutex 
{
protected :
	pthread_mutex_t m;
	friend class LUCENE_Event ;
public:
	LUCENE_Mutex()
	{
		pthread_mutex_init(&m, NULL);
	}

	~LUCENE_Mutex()
	{
		//DEBUG(DEBUG_INF,"%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
		pthread_mutex_destroy(&m);
	}

	LUCENE_S32 Lock()
	{
		//DEBUG(DEBUG_INF,"%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
		//if(0 != TryLock())
		{
			return pthread_mutex_lock(&m);
		}
	}
	LUCENE_S32 Unlock()
	{
		//DEBUG(DEBUG_INF,"%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
		return pthread_mutex_unlock(&m);
	}
	LUCENE_S32 TryLock()
	{
		//DEBUG(DEBUG_INF,"%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
		return pthread_mutex_trylock(&m);
	}

    bool is_locked()
	{
		LUCENE_S32 islock = TryLock();
		Unlock();
		return islock != 0 ? true : false;
	}
};

class LUCENE_RWLock
{
protected:
	pthread_rwlock_t rwlock;
public:
	LUCENE_RWLock()
	{
		pthread_rwlock_init(&rwlock, NULL);
	}
	~LUCENE_RWLock()
	{
		pthread_rwlock_destroy(&rwlock);
	}
	LUCENE_S32 ReadLock()
	{
		return pthread_rwlock_rdlock(&rwlock);
	}
	LUCENE_S32 TryReadLock()
	{
		return pthread_rwlock_tryrdlock(&rwlock);
	}
	LUCENE_S32 WriteLock()
	{
		return pthread_rwlock_wrlock(&rwlock);
	}
	LUCENE_S32 TryWriteLock()
	{
		return pthread_rwlock_trywrlock (&rwlock);
	}
	LUCENE_S32 Unlock()
	{
		return pthread_rwlock_unlock(&rwlock);
	}
};

template<typename Lock>
class CAutoLock
{
	public:
		CAutoLock(Lock& m)
		:_refM(m)
		{
			_refM.Lock();
		}
		~CAutoLock()
		{
			_refM.Unlock();
		}
	private:
		Lock& _refM;
	private:
		// prevent copy operations
//		Lock ( Lock & );
//		void operator = ( Lock & );
};

typedef CAutoLock<LUCENE_Mutex> CMutexAutoLock;

// �¼�����
class LUCENE_Event 
{
protected :
	bool  signal ; 
	pthread_cond_t t;
	pthread_condattr_t cattr;
public:
	LUCENE_Event() : signal(false)
	{
		pthread_condattr_init(&cattr);
		pthread_condattr_setclock(&cattr, CLOCK_MONOTONIC);
		pthread_cond_init(&t, &cattr);
	}

	~LUCENE_Event()
	{
		signal = false ;
		pthread_cond_destroy(&t);
		pthread_condattr_destroy(&cattr);
	}

	void Time(unsigned long ms, struct timespec& now)
	{
//		while(clock_gettime(CLOCK_REALTIME, &now) != 0)
//			; // -lrt ��

//		struct timeval tv;
//		gettimeofday(&tv, NULL);
		struct timespec tv;
		clock_gettime(CLOCK_MONOTONIC, &tv);

		now.tv_nsec = tv.tv_nsec;
		now.tv_sec = tv.tv_sec;

		ms += (unsigned long)(now.tv_nsec / 1000 /1000);
		now.tv_sec += ( ms / 1000) ;
		ms = (ms % 1000) ;
		/*while(ms >= 1000)
		{
		now.tv_sec++;
		ms -= 1000;
		}*/
		now.tv_nsec = ((long long)ms) * 1000 * 1000;
	}


//success return true; error or timeout return false
	bool Wait(LUCENE_Mutex& m, unsigned long ms)
	{
		bool bWait = false ;
		if (signal)
			bWait = true ;
		else
		{
			struct timespec now;
			Time(ms, now);
			int rc = WaitImpl(m, now);
			if(rc == ETIMEDOUT)
			{
				bWait = true;
			}
			else if(rc == 0)
			{
				bWait = true;
			}
		}
		signal = false ;
		return bWait ;
	}
	bool Wait(LUCENE_Mutex& m)
	{
		bool bWait = true ;
		if (signal)
			bWait = true ;
		else
		{
			bWait = WaitForSignal(m);
		}
		signal = false ;
		return bWait ;
	}
	bool LockWait(LUCENE_Mutex& m, unsigned long ms)
	{
		CMutexAutoLock lock(m);
		return Wait(m,ms);
	}
	bool LockWait(LUCENE_Mutex& m)
	{
		CMutexAutoLock lock(m);
		return Wait(m);
	}
	void Reset()
	{
		pthread_cond_destroy(&t);
		pthread_cond_init(&t, &cattr);
	}
	/**********************
	 * exit and send signal
	 ****/
	void SignalOne()
	{
		pthread_cond_signal(&t);
		signal = true ;
	}

	void SignalAll()
	{
		pthread_cond_broadcast(&t);
		signal = true ;
	}

protected :
	bool Wait(LUCENE_Mutex& m, const struct timespec & tm)
	{
		return (0 == pthread_cond_timedwait(&t, &m.m, &tm) ); // true - �ǳ�ʱ   false - ��ʱ
	}

	int WaitImpl(LUCENE_Mutex& m, const struct timespec & tm)
	{
		return pthread_cond_timedwait(&t, &m.m, &tm);
	}

	bool WaitForSignal(LUCENE_Mutex& m)
	{
		return (0 == pthread_cond_wait(&t, &m.m) ); // true - �ǳ�ʱ   false - ��ʱ
	}
};	



#endif /* MUTEX_H_ */
