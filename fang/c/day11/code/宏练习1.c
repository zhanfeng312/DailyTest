#include <stdio.h>
#define SECPH      (60 * 60)
#define NEG(n)     0 - (n)
#define SQUARE(n)  ((n) * (n)) 
int main(){

    printf("小时数是%d\n", 7200/SECPH);
    printf("NEG(3)是%d\n", NEG(3));
    printf("NEG(3 + 8)是%d\n", NEG(3 + 8));
    printf("SQUARE（4）是%d\n", SQUATR(4));
    printf("SQUARE(++value)是%d\n", SQUARE(++value));

    return 0;
}
