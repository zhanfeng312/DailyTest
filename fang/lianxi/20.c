#include <stdio.h>
int main(void){
    int a;
    scanf("%d", &a);
    int i = 0;
    if (a < 0)
        goto usage;

    for (i = 1; i <= 32; i++)
        if( (a << i) < 0)
            break;
usage:
    printf("最左边的1的位置为(总共32位):%d\n", 32-i);
    return 0;
}
