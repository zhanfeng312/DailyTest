#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct {
    uint8_t a;
    uint8_t b;
} MyStruct;

typedef struct {
    uint8_t tagId;
    uint16_t len;
    char data[0];
} VarStruct;

typedef struct {
    uint8_t a : 4;
    uint8_t b : 5;
} BitField;

static void TestStruct(void)
{
    MyStruct myStruct;
    printf("&a = %p, &b = %p\n", &myStruct.a, &myStruct.b);
}

static void TestBitField(void)
{
    printf("sizeof(BitField) = %ld\n", sizeof(BitField));

    BitField bitField;
    const uint16_t num = 0x3244; //00110010 01000100  位域不能跨字节

    (void)memcpy(&bitField, &num, sizeof(num));
    printf("bitField.a = %d, bitField.b = %d\n", bitField.a, bitField.b); // 4 18
}

static void TestVarType(void)
{
    printf("sizeof(VarStruct1) = %ld\n", sizeof(VarStruct));
}

static void TestBasicType(void)
{
    int *pointer = NULL;
    printf("sizeof(pointer) = %ld\n", sizeof(pointer));
    printf("sizeof(char) = %lu.\n", sizeof(char));
    printf("sizeof(short) = %lu.\n", sizeof(short));
    printf("sizeof(int) = %lu.\n", sizeof(int));
    printf("sizeof(long) = %lu.\n", sizeof(long));
    printf("sizeof(long long) = %lu.\n", sizeof(long long));
    printf("sizeof(float) = %lu.\n", sizeof(float));
    printf("sizeof(double) = %lu.\n", sizeof(double));

    printf("sizeof(bool) = %lu.\n", sizeof(bool));
    printf("sizeof(uint8_t) = %lu, UINT8_MAX(%u).\n", sizeof(uint8_t), UINT8_MAX);
    printf("sizeof(uint16_t) = %lu, UINT16_MAX(%u).\n", sizeof(uint16_t), UINT16_MAX);
    printf("sizeof(uint32_t) = %lu, UINT32_MAX(%u).\n", sizeof(uint32_t), UINT32_MAX);
    printf("sizeof(uint64_t) = %lu, UINT64_MAX(%lu).\n", sizeof(uint64_t), UINT64_MAX);
}

static void TestPrintf(void)
{
    /*
        %[flags][width][.precision][length]specifier
        默认右对齐
    */
    int a = 1234;
    printf("[%03d]\n", a); //前导0, 如果指定了-或精度，则忽略
    printf("[%-3d]\n", a);
    printf("[%+3d]\n", a); //输出+ / -
    printf("[% 3d]\n", -3); //输出值为正时加上空格，为负时加上负号

    printf("[%5d]\n", a);
    printf("[%*d]\n", 5, a); //宽度未通过format指定, *代表长度在后面通过常量指定

    printf("**%5d**%5.3d**%05d**%.3d**\n", 6, 6, 6, 6); //前导0
}

static void TestScanf(void)
{
    // int a, b;
    // printf("Please input two number:\n");
    // int ret = scanf("%d%*c%d", &a, &b);
    // printf("The ret is %d, a = %d, b = %d\n", ret, a, b);

    char str[50];
    scanf("%[^\n]",str); //到换行符为止
    printf("%s\n",str);
    return;
}

int main(void)
{
    // TestStruct();
    // TestBitField();
    TestBasicType();
    // TestVarType();
    // TestPrintf();
    // TestScanf();

    return 0;
}