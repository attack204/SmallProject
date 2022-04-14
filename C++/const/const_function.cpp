#include<cstdio>
#include<memory>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
void print(const string & after_column = string()) {
    cout << after_column << '\n';
}
int main() {
    string s = string();
    print(s);
    print();
    return 0;
}