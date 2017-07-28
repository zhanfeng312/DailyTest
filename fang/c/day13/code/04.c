/*
 * const指针练习
 */
#include <stdio.h>
int main(){
    int value = 3;
    const int *p_value = &value;
    int * const p_value1 = &value;  //地址本身的地址数据不能更改
    *p_value = 3;       //错误
    /*value = 7;
    *p_value1 = 5;
    //p_value1 = NULL;    //错误
    p_value = NULL;*/


    return 0;
}
