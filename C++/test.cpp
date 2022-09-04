#include<cstdio>
class Test {
    int v;
    Test operator + (const const Test b) {
        Test ret;
        ret.v = this->v + b.v;
        return ret;
    }
}
int main() {

}