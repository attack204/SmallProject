#include<iostream>
using namespace std;

class X {

};
class A: virtual X {
public:
    int sum() {
        return 1;
    }
};
class B: virtual X {

};
class D: A, B {

};

int main() {
    A a;
    cout << a.sum() << '\n';
}

