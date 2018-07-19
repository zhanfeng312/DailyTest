/*
 *数组名称的使用
 */
#include<stdio.h>
int main(){
    int arr[5] = {1,2,3,4,5};
    int i = 0;
    printf("arr是%p,&arr[1]是%p\n", arr, &arr[1]);
    //arr = 1;
    printf("&arr是%p\n",&arr);
    printf("arr + 1是%p,&arr + 1是%p\n",arr + 1,&arr + 1);
    *(arr + 3) = 13;
    printf("arr[3]是%d\n",arr[3]);
    for(i = 0;i <= 4;i++){
        printf("%d ", *(arr + i));
    }
    printf("\n");


    return 0;
}
