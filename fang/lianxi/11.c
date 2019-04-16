#include <stdio.h>
int main(void){
    char arr[5] = {0};
    scanf("%s", arr);
    char* p = arr;
    printf("%s, %s\n", arr, p);
    return 0;
}
