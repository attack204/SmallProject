package main

import "fmt"

//import "fmt"

func main() {
	arr := []int{9, 8, 7, 6};

	for i := 0; i < len(arr); i++ {
		fmt.Printf("%d\n", arr[i]);
	}
	for i, i2 := range arr {
		fmt.Printf("%d %d\n", i, i2);
	}


}
