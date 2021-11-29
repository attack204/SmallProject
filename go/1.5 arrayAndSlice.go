package main

import "fmt"

func main() {
//array
	a1 := [3]int{9, 8, 7};
	var a2 [3]int;
	fmt.Printf("a1: %v, len: %d, cap: %d\n", a1, len(a1), cap(a1));
	fmt.Printf("a2: %v, len: %d, cap: %d\n", a2, len(a2), cap(a2));
	fmt.Printf("a[1]: %d\n", a1[1]);

//slice
	s1 := []int{1, 2, 3, 4}; //直接初始化三个元素
	s2 := make([]int, 5, 6); //创建了一个包含三个元素，容量为4的切片
	s3 := make([]int, 6); //6个元素、容量为6
	//s4推荐写法，最佳实践
	//s4 := make([]int, 0,, capacity);
	fmt.Printf("%+v %d %d\n", s1, len(s1), cap(s1));
	fmt.Printf("%+v %d %d\n", s2, len(s2), cap(s2));
	fmt.Printf("%+v %d %d\n", s3, len(s3), cap(s3));


	s2 = append(s2, 7);//添加一个，未扩容
	fmt.Printf("%+v %d %d\n", s2, len(s2), cap(s2));
	s2 = append(s2, 8); //添加一个，扩容，扩大为以前的两倍，之前是6，现在是12
	fmt.Printf("%+v %d %d\n", s2, len(s2), cap(s2));


//array vs slice: 遇事不决用切片
	//子切片只推荐用读
	fmt.Printf("%+v",  s2[5:]);

}