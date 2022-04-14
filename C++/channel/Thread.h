#pragma once
 
#include "Lock.h"
 
//当定义此宏时，所有线程将只执行一次后就推出。
//#define _EXEONECE 10
 
#if defined(WIN32) || defined(WIN64)
DWORD WINAPI MyThreadProcess( void* derivedThread );
#elif defined(__linux__)
void* MyThreadProcess ( void * derivedThread );
#endif
 
 
class Thread {
 
public :
 
	enum ThreadStatus 
	{
		READY ,		// 当前线程处于准备状态
		RUNNING ,	// 处于运行状态
		EXITING ,	// 线程正在退出
		EXIT		// 已经退出 
	};
 
public :
 
	Thread ( ) ;
 
	virtual ~Thread () ;
 
public :
 
	void start () ;
 
	virtual void stop () ;
 
	void exit ( void * retval = NULL ) ;
 
	virtual void run () ;
public :
	TID getTID () const { return m_TID; }
 
	ThreadStatus getStatus () const { return m_Status; }
 
	void setStatus ( ThreadStatus status ) { m_Status = status; }
 
 
#if defined(__cplusplus) && (__cplusplus >= 201103)
	bool joinable() const {
		return m_hThread->joinable();
	}
#endif
 
 
#if defined(__cplusplus) && (__cplusplus >= 201103)
	void join() {
		return m_hThread->join();
	}
#endif
 
private :
 
	TID m_TID;
 
	ThreadStatus m_Status;
 
#if defined(__cplusplus) && (__cplusplus >= 201103)
	std::thread* m_hThread;
#else
	// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
	HANDLE m_hThread ;
#endif
#endif
 
 
};
 
extern unsigned int g_QuitThreadCount ;
 