#include <stdio.h>

int main()
{
    int a = 0;

    printf("please enter a number: ");

    scanf("%d", &a);

    printf("Oct:[%#o]\nDec:[%d]\nHex:[%#x]\n", a, a, a);

    return 0;
}
