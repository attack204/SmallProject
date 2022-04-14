#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
#include<vector> 
int N = 10;
std::string pool[10];
void init() {
    for(int i = 0; i < N; i++) {
        pool[i] = (!i) ? "a" : pool[i - 1] + "a";
    }
}
class Ptr {
public: 
    int cur;
    Ptr(int n) : cur(n) {}
    std::string & operator *() const 
    {
        return pool[cur];
    }
    std::string * operator -> () const 
    {
        return & this->operator*();
    }
};
int main() {
    init();
    Ptr *p = new Ptr(5);
    std::cout << *p->cur;

    return 0;
}