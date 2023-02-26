package main

import (
	"fmt"
)

func foo(a *[]int) {
	fmt.Println(a)
	fmt.Printf("%p\n", a)
	(*a)[2] = 0
}

func main() {
	a := []int{1, 2, 3, 4, 5, 6}
	foo(&a)
	fmt.Println(a)
	fmt.Printf("%p\n", a)
}

//[1 2 3 4 5 6]
//0x140000ba030
//[1 2 0 4 5 6]
//0x140000ba030
