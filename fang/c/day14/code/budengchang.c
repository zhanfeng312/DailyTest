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
int main(){
    printf("%d\n", max(4, 56, 100, 89, 788));
    return 0;
}
