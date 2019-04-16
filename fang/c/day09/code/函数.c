/*
 *函数练习
 */
#include <stdio.h>
int add(int value,int value1){   //小括号里声明了两个变量,即形参
   return value + value1;        //返回语句
}
void show(int i){
    printf("计算结果是:");
    printf("%d\n",i);
}

int main(){
    int value = 0;
    value = add(2, 3);          //调用函数，它所对应的就是实参
    value = add(value, 4);
    show(value);

    return 0;
}
