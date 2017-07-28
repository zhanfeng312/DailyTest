#include <stdio.h>
#define MAX(x, y) (x/y ? x : y)
int main(void){
#ifndef __cplusplus
    int a = 5, b = 2;
    printf("两个数中最大的为: %d\n", MAX(a, b));
    printf("%d\n", __LINE__);
    printf("%s\n", __FILE__);
    int c = (a^b)>>2;
    printf("%d\n", c);
#endif
    return 0;
}
