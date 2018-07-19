#include <stdio.h>
int main (void){
    unsigned int a = ~0;
    if ( a >  65536){
        printf("32位!\n");
    }
    else{
        printf("16位!\n");
    }
    return 0;
}
