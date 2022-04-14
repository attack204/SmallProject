#include "Lock.h"
 
 
void VSleep( unsigned int millionseconds ) {
#if defined(__cplusplus) && (__cplusplus >= 201103)
	std::this_thread::sleep_for(std::chrono::milliseconds(millionseconds));
#else
	// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
	Sleep( millionseconds ) ;
#elif defined(__linux__)
	usleep( millionseconds*1000 ) ;
#endif
#endif
 
}
 
TID VGetCurrentThreadId() {
#if defined(__cplusplus) && (__cplusplus >= 201103)
	return std::this_thread::get_id();
#else
	// #error "not support c++11"
#if defined(WIN32) || defined(WIN64)
	return GetCurrentThreadId( ) ;
#elif defined(__linux__)
	return pthread_self();
#endif
#endif
 
}