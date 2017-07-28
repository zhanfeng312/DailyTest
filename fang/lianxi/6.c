#include <stdio.h>
#include <string.h>
int main (void){
    char a;
    char *str = &a;
    strcpy(str, "Hello");
    printf("%s\n", str);
    return 0;
}
