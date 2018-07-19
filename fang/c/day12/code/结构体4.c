/*
 * 结构体位域练习
 */
#include <stdio.h>
typedef struct {
    int gender:1;   //占一个二进制位
    int age:6;
} stru1;
int main(){
    printf("%d\n",sizeof(stru1)); //是由对齐决定

    return 0;
}
