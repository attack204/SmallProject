#include<iostream>

using std::cout;
using std::endl;

class A {
public:
    long a;
    A() {
        a = 1;
    }
};
class B: public A{
public:
    long b;
    B() {
        b = 2;
    }
};
class C: public B {
public:
    long c;
    C() {
        c = 3;
    };
};


int main() {
    B *test = new A();
    cout << test->c << '\n';
}