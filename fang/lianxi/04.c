#include <stdio.h>
#include <unistd.h>
#define MAX(a, b) (a > b ? a : b)
int main (void){
    int a = 4;
    int b = 2;
    printf("Max = %d\n", MAX(a, b));
    return 0;
}
