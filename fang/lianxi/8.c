#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void getMemory(char *p){ //这种传参方式为值传递,只是产生了一个副本而已,
                         // 而实参不变
    p = (char*)malloc(100);
}
int main (void){
    char *str = NULL;
    getMemory(str);
    strcpy(str, "helloworld");
    printf("%s\n", str);
    return 0;
}
