#include <stdio.h>
int* func(){
    static int a = 1;
    return &a;
}
int main(void){
    int* p = func();
    printf("%d\n", *p);
    return 0;
}
