package main

import "unsafe"

type mspan struct {
	next *mspan
	prev *mspan

	startAddr uintptr //start address
	npages    uintptr // page number, each size is 8KB

	freeindex uintptr //the index to scan the free object

	allocBits  *gcBits // memory usage
	gcmarkBits *gcBits // gc situaiton
	allocCache uint64  // quickly find the un used memory, 2's complement code of allocBits

	state mSpanStateBox //state of mspan:  mSpanDead, mSpanInUse, mSpanManual, mSpanFree

	/*
		spanClass point out that the bytes(大小) and type(类型) and object number (对象个数) in mspan
		e.g. id=4, bytes/obj:48, bytes/span:8192, objects: 170
		spanClass is a 8 bytes number, the front 7 represent SpanID, the last one represent if the object has point(指针)
		spanClass有8位，前7位表示spanId，最后一位表示该对象有没有指针
	*/
	spanclass spanClass //uint8, mspan's idtype

}

type mcache struct {
	//tiny allocator分配16字节以下的微对象
	tiny       uintptr
	tinyoffset uintptr
	tinyAllocs uintptr

	//68 * 2个mspan
	alloc [numSpanClasses]*mspan // spans to allocate from, indexed by spanClass
}

type mcentral struct {
	spanclass spanClass

	//[0] swept
	//[1] unswept
	partial [2]spanSet // list of spans with a free object
	full    [2]spanSet // list of spans with no free objects
}

type mheap struct {
	lock     mutex
	allspans []*mspan
	arenas   [1 << arenaL1Bits]*[1 << arenaL2Bits]*heapArena
	central  [numSpanClasses]struct { //length is 136, 68 are nonscans and others are scans
		mcentral mcentral
		pad      [cpu.CacheLinePadSize - unsafe.Sizeof(mcentral{})%cpu.CacheLinePadSize]byte
	}
}

type heapArena struct {
	bitmap [heapArenaBitmapBytes]byte
	spans  [pagesPerArena]*mspan
	....
}

func mallocgc(size uintptr, typ *_type, needzero bool) unsafe.Pointer {
	...
	if size <= maxSmallSize {
		if noscan && size < maxTinySize {
			off := c.tinyoffset
			if off + size <= maxTinySize && c.tiny != 0 {
				x = unsafe.Pointer(c.inty + off)
				c.tinyoffset = off + size
				c.local_tinyallocs++
				releasem(mp)
				return x
			}

			span := c.alloc[tinySpanClass]
			v  := nextFreeFast(span)
			if v == 0 {
				v, _, _ = c.nextFree(tinySpanClass)
			}
			x = unsafe.Pointer(v)
			(*[2]uint64)(x)[0] = 0
			(*[2]uint64)(x)[1] = 0
			if size < c.tinyoffset || c.tiny == 0 {
				c.tiny = uintptr(x)
				c.tinyoffset = size
			}
			size = maxTinySisze

		}
	}
}

func main() {

}
