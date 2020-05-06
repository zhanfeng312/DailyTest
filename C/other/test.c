#include <stdio.h>
#include <stdint.h>

void test_yiwei(void);
void test_var_buf(void);

#define MY_LOG(fmt, ...) do {                                                 \
    printf("%s %s %d: "fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)

typedef struct {
    uint16_t len;
    char data[0];
} TestA;

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
    10000000 00000000 00000000 00000000, 右移一位(因右符号位, 保留)后变为:
    11000000 00000000 00000000 00000000
#endif
}

void test_var_buf(void)
{
    MY_LOG("sizeof(TestA) = %ld", sizeof(TestA));
}

int main(void)
{
    test_yiwei();
    test_var_buf();

    return 0;
}
