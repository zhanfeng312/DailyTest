#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error.");
        exit(1);
    }
    printf("fd = %d\n", fd);

    int newfd = dup(fd);
    printf("newfd = %d\n", newfd);

    int ret = write(newfd, "1234567", 7);
    printf("ret is %d\n", ret);

    close(fd);
    close(newfd);

    return 0;
}