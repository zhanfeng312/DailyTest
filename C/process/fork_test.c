#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    printf("xxxxxxxxxxxxx\n");

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("I'm child, pid = %u, ppid = %u\n", getpid(), getppid());
    } else {
        printf("I'm parent, pid = %u, ppid = %u\n", getpid(), getppid());
        sleep(1);
    }
    printf("yyyyyyyyyyyyyyyyyyy\n");

    return 0;
}