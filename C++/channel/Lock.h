#pragma once

#if defined(__cplusplus) && (__cplusplus >= 201103)
#include <thread>
typedef std::thread::id TID;
#else
// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
typedef DWORD TID;
#elif defined(__linux__)
#include <pthread.h> // 需要 -pthread
#include <unistd.h>
typedef pthread_t TID;
#endif
#endif

#if defined(__cplusplus) && (__cplusplus >= 201103)
#include <mutex>
class VLock
{
	std::mutex m_Lock;

public:
	void Lock() { m_Lock.lock(); }
	void UnLock() { m_Lock.unlock(); };
	bool TryLock() { return m_Lock.try_lock(); };
};
#else
//#error "not support c++11"
#if defined(WIN32) || defined(WIN64)
class VLock
{
	CRITICAL_SECTION m_Lock;

public:
	VLock() { InitializeCriticalSection(&m_Lock); }
	~VLock() { DeleteCriticalSection(&m_Lock); }
	void Lock() { EnterCriticalSection(&m_Lock); }
	void UnLock() { LeaveCriticalSection(&m_Lock); };
};
#elif defined(__linux__)
class VLock
{
	pthread_mutex_t m_Mutex;

public:
	VLock() { pthread_mutex_init(&m_Mutex, NULL); }
	~VLock() { pthread_mutex_destroy(&m_Mutex); }
	void Lock() { pthread_mutex_lock(&m_Mutex); }
	void UnLock() { pthread_mutex_unlock(&m_Mutex); };
};
#endif
#endif

//自动加锁解锁器
class AutoLock_T
{
public:
	AutoLock_T(VLock &rLock)
	{
		m_pLock = &rLock;
		m_pLock->Lock();
	}
	~AutoLock_T()
	{
		m_pLock->UnLock();
	}

protected:
private:
	AutoLock_T();
	VLock *m_pLock;
};

//当前线程挂起一定时间
extern void VSleep(unsigned int millionseconds = 0);

//获得当前线程ID
extern TID VGetCurrentThreadId();