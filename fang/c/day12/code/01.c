/*
 *多文件练习
 */
#include <stdio.h>
#include "01add.h"
#include "01sub.h"
extern int result;
int main(){
    add(3, 7);
    printf("计算结果是%d\n", result);
    printf("计算结果是%d\n", sub(3, 7));
    return 0;
}
