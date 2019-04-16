/*
 *变量练习
 */
#include <stdio.h>
int value;                      //全局变量，若没赋值，默认为0
int main(){
    printf("value是%d\n",value);
    int value = 2;
    printf("value是%d\n",value);
    {
        printf("value是%d\n",value);
        int value = 3;
        printf("value是%d\n",value);
    }

    printf("value是%d\n",value);

    return 0;
}
