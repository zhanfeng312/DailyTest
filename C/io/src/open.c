#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {

        fprintf(stderr, "usage: %s newfile\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    close(fd);

    return 0;
}