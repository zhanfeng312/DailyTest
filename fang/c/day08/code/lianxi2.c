#include <stdio.h>
int main(){
    int shu_zi = 0,n = 0;
    printf("请输入一个数字：");
    scanf("%d",&shu_zi);
    do{
        shu_zi /= 10;
        n++;
    }while(shu_zi != 0);
    
    printf("该数有%d位\n",n);
    return 0;
}
