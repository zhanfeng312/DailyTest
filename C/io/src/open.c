#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

/*
    ./a.out 1 2 3
    argc为4, argv[0]为a.out
*/
int main(int argc, char *argv[])
{
    printf("argc is %d\n", argc);
    if (argc < 2) {
        fprintf(stderr, "usage: %s newfile\n", argv[0]);
        exit(1);
    }

    //int fd = open(argv[1], O_RDONLY);
    // int fd = open(argv[1], O_RDONLY | O_TRUNC | O_CREAT , 0644); // 创建文件权限 ~umask & mode
    //当O_EXCL 与 O_CREAT同时使用时，如果文件存在open失败
    int fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    printf("fd = %d\n", fd);
    (void)close(fd);

    return 0;
}