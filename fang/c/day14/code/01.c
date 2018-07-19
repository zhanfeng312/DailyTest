/*
 * 数组指针练习
 */
#include <stdio.h>
int main(){
    //数组名称和数组名称取地址值是一样的，只是加1，对应的单位不同
    int value[5] = {0};
    int values[3][4] = {0};
    int *p_value = value;
    int (*p_value1)[5] = &value;
    printf("value是%p\n", value);
    printf("&value是%p\n", &value);

    printf("value + 1是%p\n", value + 1);
    printf("p_value + 1是%p\n", p_value + 1);

    printf("&value + 1是%p\n", &value + 1);
    printf("p_value1是%p,p_value1 + 1是%p\n", p_value1,p_value1 + 1);
    printf("values是%p,values + 1是%p\n", values,values + 1);

    return 0;
}
