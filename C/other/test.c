#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define MY_LOG(fmt, ...) do { \
    printf("%s %s %d: "fmt".\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)

void test_yiwei(void)
{
#if 0
    1. 对于常量，由于左移的位数大于了31位，所以结果为0
    2. 对于变量，如果移位的位数b大于了该类型的大小sz ，则先用b对sz取模，即 b = b % sz，然后再进行移位运算

    int a = 1;
    int b = 32;
    MY_LOG("%d %d", a << b, 1 << 32); //1, 0
#endif

    int i = 1;
    MY_LOG("[0x%08x]左移一位为:[0x%08x]", i, i << 1);

    i = 0xffffffff;
    MY_LOG("%d的二进制形式为:0x%08x", i, i);

    i = 0x80000000;
    MY_LOG("[0x%08x]左移一位为:[0x%08x]", i, i << 1);
#if 0
    左移:当为有符号数时,符号位会被移出
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 左移一位后变为:
    00000000 00000000 00000000 00000000
#endif

#if 0
    i = 1;
    MY_LOG("1左移33位为:%d", i << 33);//会给出警告,33 % 32 = 1 左移1位,i变成2
#endif

    i = 0x80000000;
    MY_LOG("[0x%08x]右移一位为:[0x%08x]", i, i >> 1);
#if 0
    右移:当为有符号数时,会保留符号位
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 右移一位(因符号位, 保留)后变为:
    11000000 00000000 00000000 00000000
#endif
}

void test_other(void)
{
#if 0
    typedef struct {
        uint16_t len;
        char data[0];
    } TestA;

    MY_LOG("sizeof(TestA) = %ld", sizeof(TestA));

    char *p = "";
    MY_LOG("p = %p:&p = %p", p, &p);
    MY_LOG("sizeof(p) = %ld", sizeof(p));

    char p1[] = "";
    MY_LOG("p1 = %p:&p1 = %p", p1, &p1);
#endif
    /*
        10000000 00000000 00000000 00000000 负数
        值等于反码+1, 反码: 01111111 11111111 11111111 11111111
        反码+1:            10000000 00000000 00000000 00000000
        所以值等于: 2 ^ 31 = 2147483648 加上负号 -2147483648


        01111111 11111111 11111111 11111111, 正数
        值等于: 等比数列前31项和              1 * (1 - 2 ^ 31) / 1 - 2 = 2 ^ 31 - 1 = 2147483647
    */
    int i = 0x80000000, j = 0x7fffffff;
    MY_LOG("i = %d, j = %d", i, j);
}

#define F1(R) #R
#define F2(R) F1(R)
#define A "192.168.51.100"
void test_macro(void)
{
//#ifndef _WIN32
# if !defined(_WIN32)
    MY_LOG("not win32");
    if (A != NULL) {
        MY_LOG("F1(A) = %s", F1(A)); // ->
        MY_LOG("F1(FANG) = %s", F1(FANG)); // ->
        MY_LOG("F2(A) = %s", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"
    }
#else
    MY_LOG("win32 not support");
#endif
}

int main(void)
{
    // test_yiwei();
    test_other();
    //test_macro();

    return 0;
}
