#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
#include<functional> //引入头文件
int add(int a, int b) {
    return a + b;
}
int main() {
    std::function<int(int, int)> f1 = add; //function本质上就是一个函数指针
    std::cout << f1(1, 2) << '\n';
    int tmp = 10, tmp2 = 11;
    //lambda表达式第一个参数是待捕获列表用来捕捉局部变量
    std::function<int(int, int)> f2 = [tmp, tmp2](int i, int j) {
        return i + j + tmp + tmp2;
    };
    std::cout << f2(3, 4);
    return 0;
}
