#include "Thread.h"
 
 
unsigned int g_QuitThreadCount = 0 ;
VLock g_thread_lock ;
 
Thread::Thread ( ) {
	try {
#if defined(__cplusplus) && (__cplusplus >= 201103)
#else
		m_TID		= 0 ;
#endif
		m_Status	= Thread::READY ;
#if defined(__cplusplus) && (__cplusplus >= 201103)
		m_hThread = new std::thread(MyThreadProcess, this);
		m_TID = m_hThread->get_id();
#else
		// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
		m_hThread = NULL ;
#elif defined(__linux__)
#endif
#endif
	} catch (...) {
 
	}
}
 
Thread::~Thread () {
}
 
void Thread::start() {
	try {
		if ( m_Status != Thread::READY )
			return ;
 
		m_Status = Thread::RUNNING;
 
#if defined(__cplusplus) && (__cplusplus >= 201103)
		m_hThread->detach();
#else
		// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
		m_hThread = CreateThread( NULL, 0, MyThreadProcess , this, 0, &m_TID ) ;
#elif defined(__linux__)
		pthread_create( &m_TID, NULL , MyThreadProcess , this );
#endif
#endif
 
	} catch (...) {
 
	}
}
 
void Thread::stop() {
 
 
}
 
void Thread::exit(void* retval) {
	try {
#if defined(__cplusplus) && (__cplusplus >= 201103)
		delete m_hThread;
		m_hThread = NULL;
#else
		// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
		CloseHandle( m_hThread ) ;
#elif defined(__linux__)
		pthread_exit( retval );
#endif
#endif
	} catch (...) {
 
	}
}
 
 
void Thread::run( ) {
 
}
 
//===================
 
 
 
#if defined(WIN32) || defined(WIN64)
 
DWORD WINAPI MyThreadProcess(  VOID* derivedThread )
{
	try
	{
		Thread * thread = (Thread *) derivedThread;
		if( thread == NULL )
			return 0;
 
		thread->run();
 
		thread->setStatus(Thread::EXIT);
 
		thread->exit(NULL);
 
		g_thread_lock.Lock() ;
		g_QuitThreadCount++ ;
		g_thread_lock.UnLock() ;
	} catch (...) {
	}
 
	return 0;	// avoid compiler's warning
}
 
#elif defined(__linux__)
 
void * MyThreadProcess ( void * derivedThread ) {
	try {
 
		Thread * thread = (Thread *)derivedThread;
		if( thread==NULL )
			return NULL;
 
		thread->run();
 
		thread->setStatus(Thread::EXIT);
 
		//INT ret = 0;
		//thread->exit(&ret);
 
		g_thread_lock.Lock() ;
		g_QuitThreadCount++ ;
		g_thread_lock.UnLock() ;
 
	} catch (...) {
 
	}
 
	return NULL;	// avoid compiler's warning
}
 
#endif