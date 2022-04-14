#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
class Test {
public:
    Test(int val): v(val) {}
    int v;
};
using TestPtr = std::unique_ptr<Test>;
int main() {
    Test a(10);
    TestPtr ptr = std::make_unique<Test>(a);
    TestPtr ptr2 = std::make_unique<Test>(a);
    std::cout << &*ptr << '\n';
    std::cout << &*ptr2 << '\n';
    return 0;
}