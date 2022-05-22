#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s hexBapHead\n", argv[0]);
        exit(1);
    }
    uint16_t result = strtoul(argv[1], NULL, 16);

    uint8_t funcId = (uint8_t)result & 0x3F; //funcId占低6bit
    uint8_t lsgId = (uint8_t)(result >> 6) & 0x3F; //lsgId占中间6bit
    uint8_t opCode = (uint8_t)(result >> 12); //opCode占最高4bit

    printf("lsgId: 0x%02x\nfuncId: 0x%02x\nopCode: 0x%02x\n", lsgId, funcId, opCode);
    return 0;
}