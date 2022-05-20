package main

import (
	"fmt"
	"time"
)

var sum int32 = 0

func add() {
	sum += 1
}

func main() {
	for i := 1; i < 1000; i++ {
		go add()
	}
	go add()
	time.Sleep(100000000)
	fmt.Println(sum)
}
