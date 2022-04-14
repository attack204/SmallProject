#include<cstdio>
#include<memory>
#include<string>
#include<iostream>
using namespace std;
int main() {
    shared_ptr<string> p1 = make_shared<string>("attack204");
    cout << *p1;
    shared_ptr<string> p2 = p1; //可以赋值
    cout << *p2;
}