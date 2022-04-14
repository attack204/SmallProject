/* 
 * File:   main.cpp
 * Author: Vicky.H
 * Email:  eclipser@163.com
 */
#include "Chan.h"
#include <iostream>
#include <thread>
 
extern bool g_ChanState;
 
void exitHook() {
    g_ChanState = false;
}
 
template<>
class ICommand<int> {
public:
	
	virtual void action (int* pResult) {
		std::cout << "Thread:" << VGetCurrentThreadId( ) << " SayHelloChain action ..." << std::endl;
		*pResult = i++;
		// VSleep(1000L);
	}
private:
	static int i;
};
 
int ICommand<int>::i = 0;
 
 
class AddCommand : public ICommand<int> {
public:
	AddCommand(int i, int j) :i (i), j(j) {
	}
 
	void action (int* pResult) {
		if (i > j) {
			int _tmp = i;
			i = j;
			j = _tmp;
		}
 
		int _sum = 0;
		for (int index = i; index < j; index++) {
			_sum += index;
		}
		*pResult = _sum;
 
		std::cout << "sum : " << _sum << std::endl;
	}
private:
	int i;
	int j;
};
 
 
/*
 * 
 */
int main(void) {
	// 测试1
//     Chain<int> chan1;
// 	
// 	ICommand<int> *pC1 = new ICommand<int>;
// 	ICommand<int> *pC2 = new ICommand<int>;
// 	ICommand<int> *pC3 = new ICommand<int>;
// 	ICommand<int> *pC4 = new ICommand<int>;
// 	ICommand<int> *pC5 = new ICommand<int>;
// 	ICommand<int> *pC6 = new ICommand<int>;
// 	chan1 < pC1;
// 	chan1 < pC2;
// 	chan1 < pC3;
// 	chan1 < pC4;
// 	chan1 < pC5;
// 	chan1 < pC6;
// 
// 	std::thread t1([&chan1](){
// 		int* pResult = new int;
// 		while (chan1 > &pResult) {
// 			std::cout << "result : " << *pResult << std::endl;
// 		}
// 	});
// 	t1.detach();
 
	// 测试2
// 	Chain<int> chan2;
// 	AddCommand* p1 = new AddCommand(0, 100);
// 	AddCommand* p2 = new AddCommand(101, 200);
// 	AddCommand* p3 = new AddCommand(201, 300);
// 	AddCommand* p4 = new AddCommand(301, 400);
// 	AddCommand* p5 = new AddCommand(401, 500);
// 	AddCommand* p6 = new AddCommand(501, 600);
// 	AddCommand* p7 = new AddCommand(601, 700);
// 	AddCommand* p8 = new AddCommand(701, 800);
// 	AddCommand* p9 = new AddCommand(801, 900);
// 	AddCommand* p0 = new AddCommand(901, 1000);
// 
// 	chan2 < p1;
// 	chan2 < p2;
// 	chan2 < p3;
// 	chan2 < p4;
// 	chan2 < p5;
// 	chan2 < p6;
// 	chan2 < p7;
// 	chan2 < p8;
// 	chan2 < p9;
// 	chan2 < p0;
// 
// 	std::thread t2([&chan2](){
// 		int sum = 0;
// 		int* pResult = new int;
// 		while (chan2 > &pResult) {
// 			sum += *pResult;
// 			std::cout << "sum : " << sum << std::endl;
// 		}
// 	});
// 	t2.detach();
 
	// 测试3
	Chan<int> chan1;
	Chan<int> chan2;
	Chan<int> chan3;
 
	AddCommand* p1 = new AddCommand(0, 100);
	AddCommand* p2 = new AddCommand(101, 200);
	AddCommand* p3 = new AddCommand(201, 300);
	
	int sum = 0;
 
	std::thread t1([&chan1, &sum](){
		
		int* pResult = new int;
		while (chan1 > &pResult) {
			sum += *pResult;
			// std::cout << "sum 1 : " << sum << std::endl;
		}
	});
	t1.detach();
 
	std::thread t2([&chan2, &sum](){
		int* pResult = new int;
		while (chan2 > &pResult) {
			sum += *pResult;
			// std::cout << "sum 2 : " << sum << std::endl;
		}
	});
	t2.detach();
 
	std::thread t3([&chan3, &sum](){
		
		int* pResult = new int;
		while (chan3 > &pResult) {
			sum += *pResult;
			// std::cout << "sum 3 : " << sum << std::endl;
		}
	});
	t3.detach();
	
	chan1 < p1;
	chan2 < p2;
	chan3 < p3;
 
 
 
	// 执行 < 很快，但执行 > 却非常慢！！！需要优化。可以考虑回调结构，或者pipe？
 
	VSleep(500L);
    
	// 打印主函数线程
	for (;;) {
		// std::cout << "Thread:" << VGetCurrentThreadId( ) << std::endl;
		VSleep(1000L);
	}
 
	atexit(exitHook);
	return 0;
}