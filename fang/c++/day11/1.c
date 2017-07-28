#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void keyPressed(){
    printf("%u", getpid());
    getchar();
}
int main (void){
    int a = 0, b = 1;
    int *p = (int*)malloc(sizeof(int));
    keyPressed();
    printf("%p-%p\n", &a, &b);
    keyPressed();
    free(p);
    return 0;
}
