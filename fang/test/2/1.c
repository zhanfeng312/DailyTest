#include <stdio.h>
#include <stdlib.h>
int main (){
    int a[] = {1, 2, 3};
    int b[] = {1, 3};
    size_t len = sizeof(a)/sizeof(a[0]), i,j;
    size_t len1 = sizeof(b)/sizeof(b[0]);
    j = (len > len1 ? len : len1);
    int *p = (int*)malloc(j*sizeof(int));

    for (i = 0; i < len; i++)
        //p[a[i]] = 1;
        *(p + a[i]) = 1;
    printf("两个整数集合的交集为:");
    for (i = 0; i < len1;i++)
        if(p[b[i]] == 1)
            printf("%d ", b[i]);
    printf("\n");
    return 0;
}
