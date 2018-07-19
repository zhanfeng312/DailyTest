/*
 * 函数练习
 */
#include<stdio.h>
int add();    // 隐式函数声明
//int add(int ,int);  //显示函数声明
int main(){
    int value = 0;
    value = add(2, 3);
    printf("%d\n",value);
    return 0;
}
int add(int value,int value1){
    return value + value1;
}
