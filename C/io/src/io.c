#include "io.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN   1024

void copy(int fdin, int fdout)
{
    char buffer[BUFFER_LEN];
    ssize_t size;

    //定位到文件尾部
    lseek(fdin, 0L, SEEK_END);
    //定位到文件开始
    lseek(fdin, 0L, SEEK_SET);
    while ((size = read(fdin, buffer, BUFFER_LEN)) > 0) {

        printf("read size: %ld\n", size);
        printf("current: %ld\n", lseek(fdin, 0L, SEEK_CUR));
        if (write(fdout, buffer, size) != size) {
            fprintf(stderr, "write error: %s\n", strerror(errno));
            exit(1);
        }
    }

    if (size < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        exit(1); //return 1 非0，不正常
    }
}