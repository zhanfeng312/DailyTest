#include "nt_common.h"
#include <stdio.h>

void test_yiwei(void)
{
/*
    移位的位数范围为0 ~ 31
    1. 对于常量，由于左移的位数大于了31位，所以结果为0
    2. 对于变量，如果移位的位数b大于31位，将所移动的位数除以32取得的余数即为移位的位数
*/
    int a = 1, b = 33;
    MY_LOG("a(%d) << b(%d) = %d", a, b, a << b); //实际移位1位, 结果为2
    //MY_LOG("1 << 33 = %d", 1 << 33); //常量左移, 结果为0

    int i = 0xffffffff;
    MY_LOG("%d的二进制形式为:0x%08x", i, i); //-1 11 11 11 11

/*
    左移:当为有符号数时,符号位会被移出 左移在后面填0
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 左移一位后变为:
    00000000 00000000 00000000 00000000
*/
    i = 0x80000000;
    MY_LOG("[0x%08x]左移一位为:[0x%08x]", i, i << 1);

/*
    右移:当为有符号数时,会保留符号位
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 右移一位(因符号位, 保留)后变为:
    11000000 00000000 00000000 00000000
*/
    i = 0x80000000;
    MY_LOG("[0x%08x]右移一位为:[0x%08x]", i, i >> 1);

    MY_LOG("-2的十六进制为: 0x%X", -2);
    MY_LOG("2的十六进制为: 0x%08X", 2);
}

int main(void)
{
    printf("CompileTime: [%s-%s]\n", __DATE__, __TIME__);

    test_yiwei();

    return 0;
}