#include <stdio.h>
int mylen(char* buf, int len){
    if (!buf[0])
        return 0;
    char* p = buf;
    int l = 0, i;
    /*for (i = 0; i < len;i++){
        if (p[i] == 32)
            break;
        else
            l++;
    }*/
    while (*p++ != 0){
        printf("%c\n", *p);
        break;
    }
    return l;
}
int main (void){
    char* array = " bcd";
    char buf[10] = {'a', 'b', '0'};
    int i = 0;
    for (;i < 10;i++)
        printf("%d ", buf[i]);
    printf("\n");
    int len = mylen (array, 5);
    //printf("%d\n", len);
    return 0;
}
