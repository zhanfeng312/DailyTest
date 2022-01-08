#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open error.");
        exit(1);
    }

    int newfd = fcntl(fd, F_DUPFD, 0);
    printf("newfd is %d\n", newfd);

    int newfd2 = fcntl(fd, F_DUPFD, 7);
    printf("newfd2 is %d\n", newfd2);

    return 0;
}