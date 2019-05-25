#include "io.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3){

        fprintf(stderr, "usage: %s srcfile destfile\n", argv[0]);
        exit(1);
    }

    int fdin, fdout;
    //打开一个待读取的文件
    fdin = open(argv[1], O_RDONLY);
    if (fdin < 0) {

        fprintf(stderr, "open error:%s\n", strerror(errno));
        exit(1);
    }
    else {
        printf("file length: %ld\n", lseek(fdin, 0L, SEEK_END));
        printf("open file: %d\n", fdin);
    }

    //打开一个待写入的文件
    fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);//粘着位，提升用户权限， 0普通方式
    if (fdout < 0) {

        fprintf(stderr, "open error: %s\n", strerror(errno));
        exit(1);
    }
    else {
        printf("open file: %d\n", fdout);
    }

    //文件拷贝
    copy(fdin, fdout);

    close(fdin);
    close(fdout);

    return 0;
}