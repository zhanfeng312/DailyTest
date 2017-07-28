/*
 * 指针练习
 */
#include <stdio.h>
int add(int value, int value1){
    value = 10;
    return value + value1;
}
int add1(int *p_value, int *p_value1){
    *p_value = 10;
    return *p_value + *p_value1;
}
int main(){
    int value = 3,value1 = 5;
    int ret = add(value, value1);
    printf("value是%d\n", value);
    printf("结果是%d\n", ret);
    ret = add1(&value, &value1);
    printf("value是%d\n", value);
    printf("结果是%d\n", ret);
    return 0;
}
