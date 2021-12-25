#include <stdio.h>

int main(void)
{
    int a = 32;
    void *p = &a;
    printf("&a = %p\n", p);
    p++;
    printf("&a++ = %p\n", p);
    return 0;
}