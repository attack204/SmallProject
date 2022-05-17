package main

import (
	"fmt"
	"time"
)

var ch1 = make(chan int)
var ch2 = make(chan int)

func first(n int) {
	for i := 0; i < n; i++ {
		<-ch1
		fmt.Println("foo")
		ch2 <- 1
	}
}
func second(n int) {
	for i := 0; i < n; i++ {
		<-ch2
		fmt.Println("bar")
		ch1 <- 1
	}
}

func main() {
	start := time.Now()
	n := 100000
	go first(n)
	go second(n)
	ch1 <- 1
	time.Sleep(time.Second / 3)
	fmt.Println("time cost", time.Since(start))
}
