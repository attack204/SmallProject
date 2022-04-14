#include<cstdio>
#include<memory>
#include<string>
#include<iostream>
using namespace std;
int main() {
    unique_ptr<string> p1(new string("attack204"));
    cout << *p1;
   // unique_ptr<string> p2 = p1;
   //wrong unique_ptr does not support assignment
}