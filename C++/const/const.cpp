#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
int f(const int &a) {
    return a;
}
int main() {

    const int a = 1;
    const int &b = a; //notice that b can't be changed
    const int aa = 2;
    //b = aa; wrong
    cout << b <<  '\n';

    int c = 2;
    const int &d = c;
    cout << d << '\n'; //允许为一个常量引用绑定非常量的对象。


    cout << f(c) << '\n';

    const int p = 1;
    const int *PointerToConst = &p; //指向常量的指针，其值可以被改变
    cout << *PointerToConst << '\n';
    int p2 = 2;
    PointerToConst = &p2; 
    cout << *PointerToConst <<  '\n'; //允许一个指向常量的指针指向一个非常量，且ptr的内容可以被改变


    int num = 1, num2 = 2;
    int *const ConstPointer = &num;
    cout << *ConstPointer << '\n';
    // ConstPointer = &num2;
    // cout << *ConstPointer << '\n';


    int num3 = 3;
    const int *const CpostPointerToConst = &num3;
    cout << CpostPointerToConst << '\n';


    return 0;
}
