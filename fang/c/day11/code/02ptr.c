/*
 *字符串练习
 */
#include <stdio.h>
int main(){
    char *p_str = "abc";   //字符串第一个字符的地址
    char ch = 'x';
    printf("%p\n","abc");
    printf("%c\n",*p_str);
    printf("%s\n",p_str);    // %s表示后面处理的是字符串，一直找，直到\0
    p_str = &ch;
    printf("%s\n",p_str);       //不可以当字符串使用
    return 0;
}
