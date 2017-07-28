#include <stdio.h>
int main (void){
    char buf[5] = {'a', 'b', 'c', 'd', 'e'};
    printf("%s\n", buf);
    int i = 0;
    for(; i < 7; ++i)
        printf("%c ", buf[i]);
    printf("\n");
    return 0;
}
