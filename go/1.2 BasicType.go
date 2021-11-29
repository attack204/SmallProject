package main

func Name(name string, age int32) (int,string) {
	return 0, "你好";
}
func Name2(name string, age int32) (a int, b string) {
	a = 1;
	b = "你好";
	return
}

func main() {
	var a int64 = 1234252;
	var b = 123;
	var (
		c int32 = 1234;
		d int16 = 1234;
	)
	println(a, b, c, d);

	const Internal = "access";
	println(Internal);

	println(Name("test", 0));
	returnb, returnc := Name2("test", 1);
	println(returnb, returnc);
}