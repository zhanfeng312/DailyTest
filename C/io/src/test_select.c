#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    fd_set readSet;
    int fd = STDIN_FILENO;
    struct timeval time = {
        .tv_sec = 5,
        .tv_usec = 0
    };
    // struct timeval time = { 5, 0 };

    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
    int ret = select(fd + 1, &readSet, NULL, NULL, &time);
    if (ret < 0) {
        printf("errno info is %s\n", strerror(errno));
    } else if (ret == 0) {
        printf("timeout\n");
    } else {
        if (FD_ISSET(fd, &readSet)) {
            char buf[512] = {0};
            ssize_t size = read(fd, buf, sizeof(buf));
            if (write(STDOUT_FILENO, buf, size) != size) {
                perror("write error");
                exit(1);
            }
        }
    }
    FD_CLR(fd, &readSet);
    return 0;
}