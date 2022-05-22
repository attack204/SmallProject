package main

import (
	"go/types"
	"sync"
	"unsafe"
)

type hchan struct {
	datasize     int32       // hchan size
	element_type *types.Type //channel type
	closed       uint32      //if closed
	lock         sync.Mutex  //control only one goroutine can send or recv
	qcount       int32       // now element number

	buf   unsafe.Pointer //stack point
	sendx int32
	recvx int32 // front and end of the circular queue

	sendq waitq //block sent goroutine
	recvq waitq //blocked recv goroutine
}
type waitq struct {
	first  *sudog
	last *sudog
}
type sudog struct { //double linked list
	g *g //one g can be on many wait lists
	next *sudog
	prev *sudog
	elem unsafe.Pointer // data
	.....

}

func send() {

}


func recv() {

}

func close() {

}

func main() {

}
