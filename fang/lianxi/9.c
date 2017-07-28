#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* getMemory(void){
    char p[] = "hello world";
    return p; //返回局部变量的地址,编译器会发出警告
}
int main (void){
    char *str = NULL;
    str = getMemory();
    printf("%s\n", str);
    return 0;
}
