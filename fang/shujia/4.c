#include <stdio.h>
int main (void)
{
    int a = 0x01;
    printf("%#x\n", htonl(a));
    return 0;
}
