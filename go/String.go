package main

import (
	"unicode/utf8"
)

func main() {
	println(len("你好")); //6
	println(utf8.RuneCountInString("你好ab")); //6
	//strings.Index()
}