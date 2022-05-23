package main

import "runtime"

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

func main() {

}