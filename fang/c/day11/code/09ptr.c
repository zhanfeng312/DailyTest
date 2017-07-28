/*
 * 条件编译练习
 */
#include <stdio.h>
//#define ONE
//#define TWO
int main(){
//#ifdef ONE
#ifndef TWO
    printf("1\n");
#else
    printf("2\n");
#endif

    return 0;
}
