/*
 * 指针练习,指针函数
 */
#include <stdio.h>
int *func(){
    static int value;       //静态局部变量生命周期被拉长到整个运行期间,但作用域仍是声明它的函数
    printf("value是%d\n",value);
    return &value;

}
int main(){
    int *p_value = NULL;
    p_value = func();
    *p_value = 7;
    func();
    return 0;
}

