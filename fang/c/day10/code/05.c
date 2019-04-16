/*
 * const关键字练习
 */
#include <stdio.h>
int main(){
    const int value = 0;        //用const声明的变量不可改
    printf("value是%d\n",value);
   // value = 3;
    value++;
    printf("value是%d\n",value);

    return 0;

}
