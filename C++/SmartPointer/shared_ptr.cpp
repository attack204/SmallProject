#include<cstdio>
#include<memory>
#include<string>
#include<iostream>
#include<array>
using std::shared_ptr;
using std::make_shared;
int main() {
    const int size = 1e6;
    for(int i = 1; i <= 1e6; i++) {
        auto p1 = std::make_shared<std::array<int, size>>();
        auto p2 = p1; //可以赋值
    }
    puts("1");
}
//10 20