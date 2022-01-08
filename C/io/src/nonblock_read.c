#include <stdio.h>
#include "io.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    char buf[512] = {0};

    SetFileStatusFlag(STDIN_FILENO, O_NONBLOCK);

    while (1) {
        ssize_t size = read(STDIN_FILENO, buf, sizeof(buf));
        if (size < 0) {
            if (errno == EAGAIN) {
                printf("Current no data, sleep 2 seconds, try again.\n");
                sleep(2);
                continue;
            } else {
                perror("read error");
                exit(1);
            }
        } else {
            if (write(STDOUT_FILENO, buf, size) != size) {
                perror("write error");
                exit(1);
            }
            break;
        }
    }

    return 0;
}