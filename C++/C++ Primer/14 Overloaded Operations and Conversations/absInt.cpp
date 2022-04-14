#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
class absInt {
public:
    int operator() (int val) const {
        return val < 0 ? -val : val;
    }
};
int main() {
    absInt a;
    int f1 = a(-1);
    int f2 = a(1);
    std::cout << f1 << ' ' << f2;
    return 0;
}