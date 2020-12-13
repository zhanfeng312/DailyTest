#include <stdio.h>
#include <stdint.h>

void test_yiwei(void)
{
#if 0
    1. 对于常量，由于左移的位数大于了31位，所以结果为0
    2. 对于变量，如果移位的位数b大于了该类型的大小sz ，则先用b对sz取模，即 b = b % sz，然后再进行移位运算
#endif

    int a = 1;
    int b = 32;
    MY_LOG("%d %d", a << b, 1 << 31);

    int i = 0xffffffff;
    MY_LOG("%d的二进制形式为:0x%08x", i, i);

#if 0
    左移:当为有符号数时,符号位会被移出
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 左移一位后变为:
    00000000 00000000 00000000 00000000
#endif

    i = 0x80000000;
    MY_LOG("[0x%08x]左移一位为:[0x%08x]", i, i << 1);

#if 0
    右移:当为有符号数时,会保留符号位
    因为0x80000000 的二进制形式为:
    10000000 00000000 00000000 00000000, 右移一位(因符号位, 保留)后变为:
    11000000 00000000 00000000 00000000
#endif
    i = 0x80000000;
    MY_LOG("[0x%08x]右移一位为:[0x%08x]", i, i >> 1);
}

void test_other(void)
{
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
}

int main(void)
{
    printf("CompileTime:%s-%s-%s-%d\n", __DATE__, __TIME__, __func__, __LINE__);
    test_yiwei();
    // test_other();

    return 0;
}
