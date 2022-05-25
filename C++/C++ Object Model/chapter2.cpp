//
// Created by 刘高吉 on 2022/5/25.
//

#include "chapter2.h"

class Dopey {  public: Dopey(); ...};
class Sneezy { public: Sneezy(int); Sneezy(); ...};
class Bashful { public: Bashful(); ...};

class Snow_White {
public:
    Dopey dopey;
    Sneezy sneezy;
    Bashful bashful;
    //...
private:
    int mumble;
};
Snow_White::Snow_White() : sneezy(1024) {
    mumble = 2048;
}
Snow_White::Snow_White() {
    deopey.Dopey::Dopey();
    sneezy(1024);
    bashful.Bashful::Bashful();
    mumble = 2048;
}
int main() {
    Snow_White snowWhite;
}