/*
 *sizeof练习
 */
#include <stdio.h>
int main(){
    int arr[] = {1,2,3,4,5};
    printf("sizeof(arr)是%d\n", sizeof(arr));
    printf("数组中变量的个数:%d\n", sizeof(arr) / sizeof(arr[0]));

    return 0;
}
