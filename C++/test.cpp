#include<cstdio>
#include<iostream>
using namespace std;
class A                     { public: void eat(){ cout<<"A";} }; 
class B: virtual public A   { public: void eat(){ cout<<"B";} }; 
class C: virtual public A   { public: void eat(){ cout<<"C";} }; 
class D: public         B,C {  }; 

int main(){ 
    D *a = new D(); 
    a->eat(); 
} 