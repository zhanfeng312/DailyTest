#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 进程扇 */
int main(void)
{
    pid_t pid;
    int i;
    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            break;
        }
    }

    sleep(i);
    if (i < 5) {
        printf("I am %d child, pid = %u\n", i + 1, getpid());
    } else {
        printf("I am parent\n");
    }
    pause();
    return 0;
}