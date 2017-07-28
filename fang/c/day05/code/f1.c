/*
 *
 *
 *
 */

#include <stdio.h>
int main(){
    int shu_zi = 300;
    unsigned char u_zi_fu = 200;
    char zi_fu = shu_zi;
    printf("%d\n",zi_fu);

    zi_fu = u_zi_fu;
    printf("%d\n",zi_fu);
    printf("%c\n",zi_fu);

    return 0;
}
