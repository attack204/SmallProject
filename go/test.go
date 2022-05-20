package main

import (
	"fmt"
)

var sum int32 = 0

func add() {
	sum += 1
}

func main() {
	fmt.Println(sum)
}
