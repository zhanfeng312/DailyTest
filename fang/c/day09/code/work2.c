#include <stdio.h>
int main(){
    int shu_zi = 0,arr[5],i = 0;
    printf("请输入一个整数:");
    scanf("%d",&shu_zi);
    for(i=0;i<5;i++)
        arr[i] = -1;

    i = 4;
    while(shu_zi != 0){
        arr[i] = shu_zi % 10;
        shu_zi /= 10;
        i--;
    }
    for(i = 0;i < 5;i++){
        if(arr[i] == -1){
            continue;
        }
        printf("%d ",arr[i]);
    }
    printf("\n");

    return 0;
}
