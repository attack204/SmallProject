#include<iostream>
using namespace std;

class X {

};
class A: virtual X {

};
class B: virtual X {

};
class D: A, B {

};

int main() {
    cout << sizeof(X) << '\n';
    cout << sizeof A << '\n';
    cout << sizeof B << '\n';
    cout << sizeof D << '\n';
}

