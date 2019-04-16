#include <stdio.h>
int sum (int a)
{
    auto int c = 0; //与int c = 0;等价，一般定义变量时默认的前缀是auto,所以没必要写.
    static int b = 3;//b是静态的,每次调用都保持着上一次调用的结果
    c+=1;
    b+=2;
    return (a+b+c);
}
void main (){
    int i;
    int a = 2;
    for (i = 0; i < 5;i++)
        printf("%d,", sum(a));
    printf("\n");
}
