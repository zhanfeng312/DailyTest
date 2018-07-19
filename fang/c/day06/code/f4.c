/*
 地址操作符
*/
#include <stdio.h>
int main(){
    int shu_zi = 0;
    printf("%p\n",&shu_zi);
    *(&shu_zi) = 3;   //地址
    printf("shu_zi是%d\n",shu_zi);

    return 0;
}
