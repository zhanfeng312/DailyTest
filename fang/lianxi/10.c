#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void getMemory(char **p, int num){
    *p = (char*)malloc(num);
}
int main (void){
    char *str = NULL;
    getMemory(&str, 100);
    strcpy(str, "hello world");
    printf("%s\n", str);
    return 0;
}
