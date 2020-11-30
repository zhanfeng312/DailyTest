#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_file(void)
{
    FILE *fp = NULL;
    const char *fileName = "fang.txt";

    fp = fopen(fileName, "w+");
    if (fp == NULL) {
        printf("open file failed\n");
        exit(1);
    }

    char buf[] = "Juan\nFang\n";
    size_t num = fwrite(buf, 1, sizeof(buf), fp);
    printf("res is %ld\n", num);

    fclose(fp);
    fp = NULL;
}

int main(int argc, char *argv[])
{
    printf("----------test file-----------\n");
    test_file();

    getchar();

    return 0;
}
