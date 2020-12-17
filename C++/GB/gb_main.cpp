#include <stdio.h>
#include <stdlib.h>
#include "gb_transfer.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s GB raw content\n", argv[0]);
        exit(1);
    }
    printf("input raw gb content is [%s]\n", argv[1]);

    GBTransfer::getInstance().ParseGBData(argv[1]);

    return 0;
}