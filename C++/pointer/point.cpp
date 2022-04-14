#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
void f(int *a) {
    *a = 10;
}
int main() {
    int a = 1; 
    cout << a << '\n';
    f(&a);
    cout << a << '\n';
    return 0;
}