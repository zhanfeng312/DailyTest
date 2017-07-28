/*
 * 指针练习
 */
#include <stdio.h>
int main(){
    int value = 0;
    int *p_value = &value,*p_value1 = &value;    // 指针变量类型为*. 用它来表示value,再加上int
    printf("p_value是%p\n",p_value);
    printf("*p_value是%d\n",*p_value);
    *p_value1 = 3;
    printf("*p_value1是%d\n",*p_value1);


    return 0;
}
