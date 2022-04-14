#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
#include<vector> 
class StrVec {
public:
    StrVec(int n) {
        size = n;
        elements = new std::string[n];
        for(int i = 1; i < n; i++) {
            elements[i] = elements[i - 1] + "a";
        }
    }
    
    std::vector<std::string> v;
    std::string & operator [] (const int &n);
    const std::string & operator [] (const int &n) const;
    StrVec operator++();
    StrVec operator++(int);

private:
    std::string *elements;
    int size;
};
std::string & StrVec::operator [] (const int &n) {
    return elements[n];
}
const std::string & StrVec::operator [] (const int &n) const  {
    return elements[n];
}
StrVec StrVec::operator++() {
    for(int i = 0; i < size; i++) {
        elements[i] += '1';
    }
    return *this;
}
StrVec StrVec::operator++(int) {
    StrVec tmp = *this;
    ++*this;
    return tmp;
}
int main() {
    StrVec strVec(10);
    for(int i = 0; i < 10; i++) {
        std::cout << strVec[i] << '\n';
    }
    StrVec tmp = strVec.operator++(); //调用前置运算符
    StrVec tmp2 = strVec.operator++(0); //调用后置运算符
    for(int i = 0; i < 10; i++) {
        std::cout << tmp[i] << '\n';
    }
    return 0;
}