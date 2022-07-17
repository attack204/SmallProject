package main

import (
	"fmt"
	"time"
)

const SIZE uint = 4 
const limit uint = 4e9
func sum(l uint, r uint, c chan uint) {
  sum := uint(0)
  for i := l; i <= r; i++ {
	sum += i ^ limit
  }
  c <- sum
}
func main() {
  start := time.Now()
  var chans [SIZE]chan uint
  for i := range chans {
	chans[i] = make(chan uint)
  }
  var ans uint
  const base uint = uint(limit / SIZE)
  for i := uint(0); i < SIZE; i++ {	
	var l uint = i * base + 1
	go sum(l, l + base, chans[i])   
  }
  for i := uint(0); i < SIZE; i++ {
	ans = ans + <- chans[i]
  }
  fmt.Println(ans)
  fmt.Println("execute time", time.Since(start))
}

