#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    int fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("open error.");
        exit(1);
    }
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("open error.");
        exit(1);
    }

    int retFd = dup2(fd1, fd2); //把fd1复制给fd2，这样fd2指向的是fd1的文件
    printf("retFd is %d\n", retFd);

    int ret = write(fd2, "1234567", 7);
    printf("ret is %d\n", ret);

    //完成重定向功能
    dup2(fd1, STDOUT_FILENO);

    printf("---------------\n");

    return 0;
}