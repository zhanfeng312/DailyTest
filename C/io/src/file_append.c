#include <stdio.h>
#include "io.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s content destfile\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[2], O_WRONLY);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }

    //设置追加的文件状态标志
    SetFileStatusFlag(fd, O_APPEND);

    // int fd = open(argv[2], O_WRONLY | O_APPEND);
    // if (fd < 0) {
    //     perror("open error");
    //     exit(1);
    // }

    //定位到文件尾部，添加了O_APPEND选项就不用lseek了
    //lseek(fd, 0L, SEEK_END);

    //往文件尾部追加内容
    size_t size = strlen(argv[1]) * sizeof(char);
    if (write(fd, argv[1], size) != size) {
        perror("write error");
        exit(1);
    }
    close(fd);

    return 0;
}