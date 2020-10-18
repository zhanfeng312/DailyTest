#include "io.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s srcfile destfile\n", argv[0]);
        exit(1);
    }

    int fdin = -1;
    int fdout = -1;

    // 打开一个待读取的文件
    fdin = open(argv[1], O_RDONLY);
    if (fdin < 0) {
        fprintf(stderr, "open error: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("file length: %ld\n", lseek(fdin, 0L, SEEK_END));
        printf("open file: %d\n", fdin);
    }

    // 打开一个待写入的文件
    fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdout < 0) {
        fprintf(stderr, "open error: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("open file: %d\n", fdout);
    }

    // 文件复制
    copy(fdin, fdout);

    (void)close(fdin);
    (void)close(fdout);

    return 0;
}