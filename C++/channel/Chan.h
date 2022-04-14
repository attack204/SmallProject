
#include "Thread.h"
 
/* 
 * File:   Chain.h
 * Author: Vicky.H
 * Email:  eclipser@163.com
 *
 * Created on 2014年4月22日, 下午3:46
 */
#pragma once
#include "Thread.h"
#include <list>
 
template<typename T>
class ICommand {
public:
    virtual void action (T* pResult) {}
};
 
extern bool g_ChanState;
 
extern VLock g_ChanStateLock;
 
 
// 通道
template<typename T>
class Chan : public Thread {
 
	template<typename E>
	friend void operator< (Chan<E>& chan, ICommand<E>* pCommand);
 
	template<typename E>
	friend bool operator> (Chan<E>& chan, E** ppResult);
public:
 
    Chan() {
        start();
    }
 
    void run() {
 
		g_ChanStateLock.Lock();
		bool _chanState = g_ChanState;
		g_ChanStateLock.UnLock();
 
        while (_chanState) {
            m_Lock.Lock();
            std::list<ICommand<T>*>::iterator it = m_Commands.begin();
			while (it != m_Commands.end()) {
				T* pResult = new T;
				(*it)->action(pResult);
				m_Results.push_back(pResult);
				it++; 
			}
			m_Commands.clear();
                
            VSleep(10L);
            m_Lock.UnLock();
 
			g_ChanStateLock.Lock();
			_chanState = g_ChanState;
			g_ChanStateLock.UnLock();
        }
    }
 
		
private:
    VLock m_Lock;
	std::list<T*> m_Results;
    std::list<ICommand<T> *> m_Commands;
};
 
	
template<typename E>
void operator< (Chan<E>& chan, ICommand<E>* pCommand) {
	chan.m_Lock.Lock();
	chan.m_Commands.push_back(pCommand);
	chan.m_Lock.UnLock();
}
 
template<typename E>
bool operator> (Chan<E>& chan, E** ppResult) {
	for (;;) {
		chan.m_Lock.Lock();
		if (!chan.m_Results.empty()) {
			break;
		}
		chan.m_Lock.UnLock();
 
		VSleep(10L);
	}
 
	AutoLock_T __lock(chan.m_Lock);
	if (chan.m_Results.empty()) {
		return false;
	}
	*ppResult = *(chan.m_Results.begin());
	chan.m_Results.pop_front();
	return true;
}