#include <stdio.h>
#include <stdint.h>

typedef union {
    unsigned short a;
    unsigned char b[2];
} ByteOrder;

typedef struct {
    uint8_t a : 2;
    uint8_t b : 3;
    uint8_t c : 3;
} BitOrder;

/*
    数据在网络中的传送顺序：
    一般而言, 网络字节序是大端字节序，即在网络中传送的数据都是按照大端方式传送，先传送高位字节，再传送低位字节;
    在传送一个字节时，总是按照小端方式传送，先传送一个字节的低位bit，再传送一个字节的高位bit.
*/
int main(void)
{
    /* 查看字节序 */
    ByteOrder byteOrder;
    byteOrder.a = 0x1234;

    printf("low address %p : byte 0x%x\n", &byteOrder.b[0], byteOrder.b[0]);
    printf("hign address %p : byte: 0x%x\n", &byteOrder.b[1], byteOrder.b[1]);

    /* 查看比特序 */
    uint8_t a = 0x66; //01100110
    BitOrder *bitOrder = (BitOrder *)&a;
    printf("low 2 bit %u\n", bitOrder->a); //2
    printf("mid 3 bit %u\n", bitOrder->b); //1
    printf("high 3 bit %u\n", bitOrder->c); //3

    return 0;
}