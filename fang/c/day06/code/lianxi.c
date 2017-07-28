/*
 *三目操作符练习
 */

#include<stdio.h>
int main(){

    int shu_zi = 0;
    printf("请输入一个整数:\n");
    scanf("%d",&shu_zi);
    shu_zi = shu_zi >= 100 ? shu_zi - 100 : 100 - shu_zi;
    printf("输入的数与100相差%d\n",shu_zi);

    return 0;
}
