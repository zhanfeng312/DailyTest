#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    char a[] = "assaf";
    int  len = strlen(a);
    char *p = (char*)malloc(len); //动态申请len个字节长度的空间
    int i = 0, j = len - 1,k = 0;
    for (;i < j;i++,j--) {
        if (a[i] == a[j]){
            *(p+k) = a[i];
            k++;
        }
    }
    for (i = k-1; i >= 0; i--)
        printf("%c", *(p+i));
    printf("\n");
    free(p);
    p = NULL;
    return 0;
}
