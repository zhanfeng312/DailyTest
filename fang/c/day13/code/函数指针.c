/*函数指针练习
 */
#include<stdio.h>
int add(int value, int value1) {
    return value + value1;
}
int sub(int value, int value1) {
    return value - value1;
}
int main(){
    int (*p_func)(int, int) = NULL; //函数指针变量的声明
    typedef int (*t_func)(int, int); //函数指针类型的声明语句
    t_func p_func1 = NULL;           //函数指针类型去声明函数指针变量
    printf("add是%p\n",add);
    p_func = add;
    printf("计算结果是%d\n", p_func(3, 6));

    p_func = sub;
    printf("计算结果是%d\n", p_func(3, 6));

    p_func1 = add;
    printf("计算结果是%d\n", p_func1(3, 6));

    p_func1 = sub;
    printf("计算结果是%d\n", p_func1(3, 6));

    return 0;
    
}
