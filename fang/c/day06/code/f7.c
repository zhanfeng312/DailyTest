/*
 *
 *大小些转换
 *
 *
 * */
#include<stdio.h>
int main(){
    unsigned char c1 = 0,c2 = 0;
    printf("请输入一个字符:\n");
    scanf("%c",&c1);
    c2 = c1 & 223;
    printf("%c\n",c2);

    return 0;
}
