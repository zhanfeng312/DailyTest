/*
 * 字符串函数练习
 */
#include <stdio.h>
#include<string.h>
int main(){
    char str[20] = "abc";
    printf("长度是%d\n",strlen("abcdef"));
    strcat(str, "xyz");  //第二个加到第一个后面，返回值交给str
    printf("合并后是%s\n",str);
    strcpy(str, "uvw");
    printf("复制后字符串是%s\n",str);
   printf("%d\n", strcmp("abc","adc"));



    return 0;
}
