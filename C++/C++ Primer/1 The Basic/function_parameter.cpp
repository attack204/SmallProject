#include<cstdio>
#include<memory>
#include<string>
#include<iostream>
using namespace std;
void f1(int n) {
    n = 5;
}
void f2(int *n) {
    cout << n << '\n'; //0x16fbbb37c
    *n = 5;
    n = new int;
    cout << n << '\n'; //0x6000000b8040。即使这里改了n的地址，实参n的地址也不会变
}
void f3(int &n)
{
    cout << &n <<  '\n'; //0x16fbbb37c
    n=1;
}
int main() {
    int n = 10;
    f1(n);
    cout << n << '\n';  //10

    f2(&n);
    cout << n << '\n'; //5。指针传参是传了地址值。

    f3(n);
    cout << n << '\n';  //引用传参。传递了该变量本身。

}
