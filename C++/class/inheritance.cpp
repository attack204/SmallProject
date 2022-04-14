#include<cstdio>
#include<memory>
#include<string>
#include<iostream>
using namespace std;
class A {
public:
    explicit A(int data_): data(data_), data2(data + 1) {

    }
    int getData() {
        return data;
    }
    int getData2() {
        return data2;
    }
private:
    int data;
    int data2;
};
int main() {
    A *a = new A(1);
    cout << (*a).getData() << '\n';
    cout << (*a).getData2() << '\n';
}