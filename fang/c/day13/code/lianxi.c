/*
 * 二级指针练习
 */
#include <stdio.h>
void func(int *p_value) {
    *p_value = 3;
}
void func1(int **pp_value) {
    *pp_value =(int *)0x12345678;
}
int main(){
    int value = 0;
    int *p_value = NULL;
    func(&value);
    printf("value是%d\n", value);
    func1(&p_value);
    printf("p_value是%p\n",p_value);


    return 0;
}
