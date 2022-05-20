package main

import (
	"runtime"
	"unsafe"
)

//Goroutine init

func (s * state) call(n *Node, k callKind) *ssa.Value {
	...
	call = s.newValue1A(ssa.OpStaticCall, types.TypeMem, newproc, s,mem())
	...
}

func newproc(siz int32, fn *funcval) {
	argp := add(unsafe.Pointer(&fn), sys.PtrSize) // 将函数指针添加到P中
	gp := getg() //获取一个Goroutine
	pc := getcallerpc() //获取调用方的程序计数器
	systemstack(func()) {
		newg := newproc1(fn, argp, siz, gp, pc) //调用newproc1，初始化Goroutine，
		_p_ := getg().m.p.ptr()
		runqput(_p_, newg, true)//将Goroutine添加到P中
		if mainStarted {
			wakep() // 满足条件时执行Goroutine
		}
	}
}

func newproc1(fn *funcval, argp unsafe.Pointer, narg int32, callergp *g, callerpc uintptr) *g {
	_g_ := getg()
	siz := narg
	siz = (siz + 7) & 7

	_p_ := _g_.m.p.ptr()
	newg := gfget(_p_)//先从P的空闲列表中查找g
	if newg == nil { //P中没有空闲的Goroutine
		newg = malg(_StackMin) // 申请一个g, 大小为2KB
		casgstatus(newg, _Gidle, Gdead)
		allgadd(newg) // 把新建的Goroutine添加到全局G中
	}

	//接下来把函数参数都复制到栈上
	memmove(unsafe.Pointer(spArg), argp, uintptr(narg))
	//接下来让Goroutine的栈指针指向上面的地址, 并设置相关参数
	memclrNoHeapPointers(unsafe.Pointer(&newg.sched), unsafe.Sizeof(newg.sched))
	newg.sched.sp = sp
	newg.sched.g = guintptr(unsafe.Pointer(newg))
	newg.ancestors = saveAncestors(callergp) //记录调用的g是哪一个
	...
	return newg
}


type P struct {

	status uint32 //五种状态字段

	m muintpr//point to M

	runq [256]guintptr // Groutine queue
	runqhead uint32
	runqtail uint32

	G* gfree;
}


// definition of g
type g struct {
	stack stack //栈内存的范围[stack.lo, stack.hi)

	//下面是与调度有关的字段
	preempt bool
	preemptStop bool

	m *m; //由哪个m持有
	sched gobuf; /*
	type gobuf struct {
		sp uintptr //stack pointer
		pc uintptr //程序计数器
		g guintpr // 由哪个g持有
	}
	*/

	atomicsstatus uint32;//g的状态，有9种情况

}

//
type m struct {
	//G
	g0 *g //持有调度栈的Goroutine
	curg *g //在当前线程上运行的Goroutine

	//P
	p puintptr //当前处理器上的p
	nextp puintptr //nextp暂存的处理器
	oldp puintptr //执行系统调用之前使用线程的处理器oldp
}

type schedt struct {
	runq gQueue //global runnable queue (全局处于运行状态的g队列)
	gFree struct { //global cache of dead G's
		stack gList //Gs with stacks
		noStack gList //Gs without stacks
	}

	// freem is the list of m's waiting to be freed when their
	// m.exited is set. Linked through m.freelink.
	freem *m
}

//1. try to take one from p.gFree[]
//2. if fail move 32 g from schedt.gFree to p.gFree[]
//3. if fail too, create one by func malg
func fgget(_p_ *p) *g {
	if _p_.gFree.empty() && (!sched.gFree.stack.empty() || ! sched.gFree.noStack.empty()) {
		for _p_.gFree.n < 32 {
			gp := sched.gFree.stack.pop()
			if gp == nil {
				gp = sched.gFree.noStack.pop()
				if gp == nil {
					break
				}
			}
			_p_.gFree.push(gp)
		}
		goto retry
	}
	gp := _p_.gFree.pop()
	if gp == nil {
		return nil
	}
	return gp
}

/*
1. if next is true. set p's runqnext = g
2. else if p's runq size < 256 add it to p's runq
3. else add it to global g(allg)
 */
func runqput(_p_ *p, gp *g, next bool) {
	if next {
	retryNext:
		oldnext := _p_.runnext
		if !_p_.runnext.cas(oldnext, guintptr(unsafe.Pointer(gp))) {
			goto retryNext
		}
	} else _p_.runq.size < 256 {
		_p_.runq[t%uint32(len(_p_.runq))].set(gp)
	} else {
		put it to global queue
	}
}

func schedule() {
	//1. 获取可以运行的Goroutine，可能从allg中，也可能从P的runq[]中(利用了比例份额的思想)
	gp := getgp()
	//2. 执行得到的gp
	execute(gp)
}
func execute(gp *g) {//初始化g的信息，将其绑定到M上
	_g_ := getg()
	gp.m = _g_.m
	_g_.m.curg = gp
	gogo(&gp, sched)
}
func gogo() {//此处为汇编实现
	//使用汇编语言执行函数
	...
	CALL runtime.goexit0(SB)
	....
}
func goexit0(gp *g) {
	//运行一段时间后重新将gp加入空闲列表
	gfput(_g_.m.p.ptr(), gp)
	schedule()//重新执行调度函数
}
