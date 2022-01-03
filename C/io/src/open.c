#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s newfile\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, 0644);
    // int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777); // 创建文件权限 ~umask & mode
    // int fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL); //当O_EXCL 与 O_CREAT同事使用时，如果文件存在open失败
    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    printf("fd = %d\n", fd);
    close(fd);

    return 0;
}