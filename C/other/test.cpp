#include <stdio.h>
#include <iostream>
#include <memory.h>

using namespace std;

struct A
{
    int a:5;
    int b:3;
};

int main(void)
{
    char str[100] = "0134324324afsadfsdlfjlsdjfl";
    struct A d;
    
    printf("sizeof(A) = %ld\n", sizeof(A));
    memcpy(&d, str, sizeof(A));
    cout << d.a << endl;
    cout << d.b << endl;
    return 0;
}