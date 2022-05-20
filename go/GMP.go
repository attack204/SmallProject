package main


struct P {
	Lock;
	uint32 status;
	P* link;
	uint32 tick;

	M* m;//point to M
	MCache* mcache;

	G** runq; // Groutine queue
	int32 runqhead;
	int32 runqtail;
	int32 runqsize;
	int32 runnext;//next Goroutine to be executed

	G* gfree;
	int32 gfreecnt;
}
