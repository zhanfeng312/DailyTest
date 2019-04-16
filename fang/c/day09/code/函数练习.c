/*
 *函数练习
 */
#include <stdio.h>
#include <stdlib.h>
void func(){
    printf("abc\n");
    exit(0);
    //return ;
    printf("def\n");
}
int main(){
    func();
    printf("xyz\n");
    return 0;
}
