/*
 *
 *移位操作
 *
 *
 * */
#include<stdio.h>
int main(){
    printf("0xabcdef89 << 2 是0x%x\n",0xabcdef89 << 2);
    printf("0xabcdef89 >> 2 是0x%x\n",0xabcdef89 >> 2); //默认为无符号类型
    printf("(int)0xabcdef89 >> 2 是0x%x\n",(int)0xabcdef89 >> 2);
    printf("最大正整数为:%d\n",~(1 << 31) );

    return 0;
}
