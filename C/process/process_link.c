#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 进程链 */
int main(void)
{
    pid_t pid;
    int i = 0;

    printf("parent process: %u\n", getpid());

    for (; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error.");
            exit(1);
        } else if (pid > 0) { //parent process
            break;
        } else { //child process
            printf("I am %dth process, pid: %u, ppid: %u\n", i+1, getpid(), getppid());
        }
    }
    pause();
    return 0;
}