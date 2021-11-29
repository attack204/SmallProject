package main

func main() {
	var a int32 = 64;
	if a > 10 {
		print("> 10\n");
	} else {
		print("< 10\n");
	}

	switch a {
		case 64:
			println("= 64");
	default:
		println("not = 64");
	}


}
