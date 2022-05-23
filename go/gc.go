package main

import (
	"runtime"
	"sync/atomic"
	"unsafe"
)

type workType struct {
	full  lfstack
	empty lfstack
	pad0  cpu.CacheLinePad

	wbufSpans struct {
		lock mutex
		free mSpanList
		busy mSpanList
	}

	...
	nproc uint32
	tstart int64
	nwait uint32
	ndone uint32
	...
	mode gcMode //gc mode, gc模式
	cycles uint32 //gc cycles, gc循环次数
	...
	stwprocs, maxprocs int32
	...
}


func (t gcTrigger) test() bool {
	if !memstats.enablegc || panicking != 0 || gcphase != _GCoff {
		return false
	}
	switch t.kind {
	case gcTriggerHeap:
		return memstats.heap_live >= memstats.gc_trigger
	case gcTriggerTime:
		if gcpercent < 0 {
			return false
		}
		lastgc := int64(atomic.Load64(&memstats.last_gc_nanotime))
		return lastgc != 0 && t.now - lastgc > forcegcperiod
	case gcTriggerCycle:
		return int32(t.n - work.cycles) > 0
	}
	return true
}

func gcStart(trigger gcTrigger) {
	for trigger.test() && sweepone() != uintptr(0) {
		sweep.nbgsweep++
	}

	semacquire(&work.startSema)
	if !trigger.test() {
		semrelease(&work.startSema)
		return
	}
	...
}


func gcStart(trigger gcTrigger) {
	...
	semacquire(&worldsema)
	gcBgMarkStartWorkers() //1. start mark workers
	work.stwprocs, work.maxprocs = gomaxprocs, gomaxprocs
	...
	systemstack(stopTheWorldWithSema) //2. stop the world
	systemstack(func() {
		finishsweep_m() //3. clear last gc's work
	})
	work.cycles++
	gcController.startCycle() //4. gc start
}

func gcStart(trigger gcTrigger) {
	...
	setGCPhase(_GCmark)

	gcBgMarkPrepare()
	gcMarkRootPrepare()

	atomic.Store(&gcBlackenEnabled, 1)
	systemstack(func() {
		now = startTheWorldWithSema(trace.enabled)
		work.pauseNS += now - work.pauseStart
		work.tMark = now
	})
	semrelease(&work.startSema)
}

func stopTheWorldWithSema() {
	...
	sched.stopwait = gomaxprocs
	for _, p := range allp {
		s := p.status
		if s == _Psyscall && atomic.Cas(&p.status, s, _Pgcstop) { //set the p's status
			p.syscalltick++
			sched.stopwait-- //record the number of P that stoped
		}
	}
	...
}

func gcBgMarkStartWorkers() {
	for gcBgMarkWorkerCount < gomaxprocs {
		go gcBgMarkWorker() //start ncpu MarkWorker 启动ncpu个MarkWorker

		notetsleep(&work.bgMarkReady, -1)
		noteclear(&work.bgMarkReady) //gopark after starting, waiting to be called

		gcBgMarkWorkerCount++
	}
}


func (c *gcControllerState) findRunnableGCWorker(_p_ *p) *g {
	...
	//set p's statue 设置p的状态
	if decIfPositive(&c.dedicatedMarkWorkersNeeded) {
		_p_.gcMarkWorkerMode = gcMarkWorkerDedicateMode
	} else {
		delta := nanotime() - gcController.markStarTime
		if delta > 0 && float64(_p_.gcFractionalMarkTime) / float64(delta) > c.fractionalUtilizationGoal {
			return nil
		}
		_p_.gcMarkWorkerMode = gcMarkWorkerFractionalMode
	}
	gp := _p_.gcBgMarkWorker.ptr()
	casgstatus(gp, _Gwaiting, _Grunnable) // modify goroutine's status 修改gourinte的状态
	return gp
}


func gcBgMarkWorker() {
	...
	switch pp.gcMarkWorkerMode {
	case gcMarkWorkerDedicateMode:
		...
		gcDrain(&_p_.gcw, gcDrainFlushBgCredit)
	case gcMarkWorkerFractionalMode:
		gcDrain(&_p_.gcw, gcDrainFractional | gcDrainUntilPreempt | gcDrainFlushBgCredit)
	case gcMarkWorkerIdleMode:
		gcDrain(&_p_.gcw, gcDrainIdle | gcDrainUntilPreempt | gcDrainFlushBgCredit)
	}
	...
}

type gcWork struct {
	wbuf1, wbuf2 *workbuf
	...
}

type workbufhdr struct {
	node lfnode
	nobj int
}
type workbuf struct {
	workbufhdr
	obj [(_WorkbufSize - unsafe.Sizeof(workbufhdr{})) / sys.PtrSize] uintptr
}

func gcDrain(gcw *gcWork, flags gcDrainFlags) {
	...
	if work.markrootNext < work.markrootJobs {
		for !(preemptible && gp.preempt) {
			job := atomic.Xadd(&work.markrootNext, +1) - 1
			if job >= work.markrootJobs {
				break
			}
			markroot(gcw, job) //here !
			if check != nil && check() {
				goto done
			}
		}
	}

	...
	scanobject(b, gcw)
	greyobject()
	...


}

func main() {

}