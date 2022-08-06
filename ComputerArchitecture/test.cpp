#include<iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    short *numPtr = new short(7), result;
    void *genPtr = numPtr;
    result = *static_cast<short *>(genPtr) + 7;
    cout << result;
    /* code */
    return 0;
}
