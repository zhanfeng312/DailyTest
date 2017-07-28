/*
 * 静态变量练习
 */
#include <stdio.h>
//static int value = 0;
void f() {
    static int value = 0;           //生命周期和作用域不一样
    printf("value是%d\n",value);
    value++;
}
int main(){
    f();
    f();
    return 0;
}
