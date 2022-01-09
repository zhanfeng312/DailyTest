#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    int flag = fcntl(STDIN_FILENO, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);

    int i = 0;
    for (; i < 5; i++) {
        char buf[512] = {0};
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