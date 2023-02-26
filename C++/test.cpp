#include <iostream>
using namespace std;
 
struct a {
    int b;
};
struct b {
    int c;
};
int main()
{
    a tt{1};
    b c = reinterpret_cast<b>(tt);
    printf("%d\n", c);
}