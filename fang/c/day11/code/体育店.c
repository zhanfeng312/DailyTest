/*
 条件编译练习
 */
#include <stdio.h>
int main(){
#if defined(ELITE)
    printf("120%%\n");
#elif defined(FACTORY)
    printf("100%%\n");
#else
    printf("80%%\n");
#endif

    return 0;
}
