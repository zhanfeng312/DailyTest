#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void TestStruct()
{
    typedef struct {
        uint8_t a;
        uint8_t b;
    } MyStruct;

    MyStruct myStruct;
    printf("&a = %p, &b = %p\n", &myStruct.a, &myStruct.b);
}

static void TestBitField()
{
    typedef struct {
        uint8_t a : 4;
        uint8_t b : 5;
    } TestBitField;

    printf("sizeof(TestBitField) = %ld\n", sizeof(TestBitField));

    TestBitField bitField;
    const uint16_t num = 0x3244; //00110010 01000100
    (void)memcpy(&bitField, &num, sizeof(num));
    printf("bitField.a = %d, bitField.b = %d\n", bitField.a, bitField.b);
}

static void TestVarType(void)
{
    typedef struct {
        uint8_t tagId;
        uint16_t len;
        char data[0];
    } VarStruct1;

    typedef struct {
        uint8_t tagId;
        uint16_t len;
        char data[0];
    } __attribute__((__packed__)) VarStruct2;

    printf("sizeof(VarStruct1) = %ld, sizeof(VarStruct2) = %ld\n", sizeof(VarStruct1), sizeof(VarStruct2));
}

static void TestBasicType(void)
{
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
    int a = 3;
    printf("[%3d]\n", a);
    printf("[%03d]\n", a);
    printf("[%-3d]\n", a);
}

static void TestScanf(void)
{
    return;
}

int main(void)
{
    // TestStruct();
    // TestBitField();
    // TestBasicType();
    // TestVarType();
    // TestPrintf();
    // TestScanf();

    return 0;
}