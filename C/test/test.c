#include <stdio.h>

#define A "123"
const char *sample_version = "fang" "zhan" "feng" A;

int main(int argc, char *argv[])
{
    printf("%s\n", sample_version);
    return 0;
}
