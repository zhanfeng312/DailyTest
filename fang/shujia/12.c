#include <stdio.h>
int main(void){
    srand( time (NULL));
    int a = rand () % 26 + 1;
    printf("%d\n", a);
    return 0;
}
