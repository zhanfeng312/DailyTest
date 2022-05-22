#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//根据lsgId, funcId, opCode得到bap头, 0x33 0x20 0x02 -->2CE0

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: %s lsgId funcId opCode\n", argv[0]);
        exit(1);
    }
    unsigned long lsgId = strtoul(argv[1], NULL, 16);
    unsigned long funcId = strtoul(argv[2], NULL, 16);
    unsigned long opCode = strtoul(argv[3], NULL, 16);

    uint16_t tmpOpCode = (uint16_t)opCode << 12; //opCode占最高4bit
    uint16_t tmpLsgId = (uint16_t)lsgId << 6; //lsgId占中间6bit
    uint16_t result = tmpOpCode | tmpLsgId | (uint16_t)funcId;

    printf("%X\n", result);
    return 0;
}