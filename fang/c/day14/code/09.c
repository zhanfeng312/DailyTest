/*
 * 变长参数练习
 */
#include <stdio.h>
#include <stdarg.h>
int max(int cnt, ...) {
    int ret = 0,loop = 0;
    va_list v;
    va_start(v, cnt);
    for(loop = 0;loop < cnt;loop++) {
        int value = va_arg(v, int);
        if(value > ret)
            ret = value;
    }
    return ret;
}
int main() {
    printf("max(2, 9, 6)是%d\n", max(2, 9, 6));
    printf("max(3, 19, 25, 2)是%d\n" ,max(3, 19, 25, 2));
    return 0;
}
