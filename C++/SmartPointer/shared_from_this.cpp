#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
class Test: public std::enable_shared_from_this<Test> {
public:
    Test() = default;
    //enable_shared_from_this允许在函数内部获取指向该对象的shared_ptr指针
    std::shared_ptr<Test> getPtr() {
        return shared_from_this();
    }
    int getValue() const {
        return value;
    }
private:
    const static int value = 10;
}; 
int main() {
    Test* a = new Test();
    std::shared_ptr<Test> ptr(a);
    std::cout << a->getPtr()->getValue();
    return 0;
}