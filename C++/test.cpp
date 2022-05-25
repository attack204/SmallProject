#include<iostream>

using std::cout;
using std::endl;

struct A {
public:
    int a;
    A(int _a) {
        a = _a;
    }
    A(const A &obj) {
        cout << "调用拷贝构造函数" << '\n';
        a = obj.a + 1;
    }
};

int main() {
    A a1(233);
    A a2 = a1; //调用拷贝构造函数
    cout << a2.a;
}