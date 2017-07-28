//当不知道执行那个函数时，用函数指针
#include <stdio.h>
int add(int value, int value1) {
    return value + value1;
}
int sub(int value, int value1) {
    return value - value1;
}
int main(){
    int (*p_func)(int, int) = NULL;
    int opr = 0;
    printf("请输入一个整数:");
    scanf("%d",&opr);
    if(opr) {
        p_func = sub;
    }
    else {
        p_func = add;
    }
    printf("计算结果为%d\n",p_func(2, 3));
    return 0;
}
