package main

import (
	"fmt"
	"time"
)

type test struct {
	x int
}

var ch = make(chan *test, 5)

func rev() {
	for i := 1; i < 10; i++ {
		fmt.Println("recv", i, "begin")
		x := <-ch
		fmt.Println(x)
		fmt.Println("recv", i, "end")
	}
}

func send() {
	for i := 1; i < 10; i++ {
		t := &test{x: i}
		fmt.Println("send ", i, "begin")
		ch <- t
		fmt.Println("send ", i, "end")
	}
}

func main() {
	go send()
	go rev()

	time.Sleep(10000000)
}
