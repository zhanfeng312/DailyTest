#include <stdio.h>
int main (void){
    int a = 5, b = 3;
    printf("max = %d\n", (a + b + abs(a-b))/2);
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
