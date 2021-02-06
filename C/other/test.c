#include "nt_common.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint16_t len;
    char data[0];
} VarStruct;

typedef struct {
    uint8_t a : 4;
    uint8_t b : 7;
} TestField;

void test_yiwei(void)
{
/*
    移位的位数范围为0 ~ 31
    1. 对于常量，由于左移的位数大于了31位，所以结果为0
    2. 对于变量，如果移位的位数b大于31位，将所移动的位数除以32取得的余数即为移位的位数
*/
    int a = 1, b = 33;
    MY_LOG("a = %d, b = %d, a << b = %d", a, b, a << b); //实际移位1位, 结果为2
    //MY_LOG("1 << 33 = %d", 1 << 33); //常量左移, 结果为0

    int i = 0xffffffff;
    MY_LOG("%d的二进制形式为:0x%08x", i, i);

/*
    左移:当为有符号数时,符号位会被移出
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
}

void test_other(void)
{
    MY_LOG("sizeof(VarStruct) = %ld", sizeof(VarStruct));
    MY_LOG("sizeof(TestField) = %ld", sizeof(TestField));

    TestField testField; //a: 4, b: 5
    uint16_t num = 0x3244;
    //00110010 01000100
    (void)memcpy(&testField, &num, sizeof(num));
    printf("testField.a = %d, testField.b = %d\n", testField.a, testField.b);

    char *p = "";
    MY_LOG("&p = %p", &p);
    MY_LOG("sizeof(p) = %ld", sizeof(p));

    char p1[] = "";
    MY_LOG("p1 = %p : &p1 = %p", p1, &p1); //字符数组, p1就是数组的地址，值和&p1相同

    const char *buf = "123";
    uint8_t a = buf[0];
    printf("a = %u\n", a);
    a = '0';
    printf("a = %u\n", a);
    a = '9';
    printf("a = %u\n", a);
    a = 0xEF;
    printf("a = %u\n", a);

    if (-1 > 2U) { //有符号和无符号数比较时, 当无符号比较
        printf("-1 > 2u\n");
    }
}

int main(void)
{
    printf("CompileTime: [%s-%s]\n", __DATE__, __TIME__);
    // test_yiwei();
    test_other();

    return 0;
}
