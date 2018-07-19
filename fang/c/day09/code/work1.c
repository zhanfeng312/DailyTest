/*
 *数组练习
 *
 */
#include <stdio.h>
int main(){
    int arr[5],i= 0;    //数组声明
    for(i = 0;i<5;i++){
        arr[i] = i+1;
    }
    for(i = 4;i >= 0;i--){
         printf("%d\t",arr[i]);
    }
    printf("\n");

    return 0;
}
