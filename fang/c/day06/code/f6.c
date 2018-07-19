/*
 *三目操作符练习
 *
 * */
#include<stdio.h>
int main(){
    int shu_zi = -3;
    shu_zi =  shu_zi < 0 ? 0-shu_zi  : shu_zi;
    printf("shu_zi是%d\n",shu_zi);
    return 0;
}
