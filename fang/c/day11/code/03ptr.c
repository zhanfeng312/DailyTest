#include <stdio.h>
int main(){
  // char *p_str = "abcdef";  //字面值
   char str[] = "abc";
  // char str[3] = "abc";//错误
  //char str2[] = {'a','b','c'};        错误
 // char str3[] = {'a','b','c',0};
   //*p_str = 'x';  字符串的字面值不可以修改，即定义好了的话，就改不了
  /* printf("%p\n","abcdef");
   printf("p_str是%p\n",p_str);
   printf("%s\n","abc""xyz");*/
   printf("%s\n",str);
   printf("字符变量个数%d\n", sizeof(str)/sizeof(str[0]));
   str[0] = 'y';
   str[1] = '\0';
   printf("%s\n",str);     //输出y*

    return 0;
}

