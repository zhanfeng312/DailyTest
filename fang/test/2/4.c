#include <stdio.h>
#include <stdlib.h>
int main (){
    int a[] = {1, 2, 3};
    int b[] = {1, 3};
    size_t len = sizeof(a)/sizeof(a[0]), i,j;
    size_t len1 = sizeof(b)/sizeof(b[0]);
    j = (len > len1 ? len : len1);
    int *p = (int*)malloc(j*sizeof(int));
    free (p);
    p = NULL;
    return 0;
}
