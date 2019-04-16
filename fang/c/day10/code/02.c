#include <stdio.h>
int stack[10], i = 0;       //全局变量
void push(int value)
{
    stack[i] = value;
    i++;
}
int pop()
{
    i--;
    return stack[i];
}
int empty()
{
    return 0 == i;
}
int full()
{
    return 10 == i;
}
int main(){

    push(4);
    push(5);
    printf("栈中元素个数为%d\n",i);
    printf("栈是否满:(1为满，0不满）%d\n",full());
       
    return 0;
}
