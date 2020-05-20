#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void sig_handler(int signo)
{
    printf("child process deaded, signo: %d\n", signo);
    //当父进程捕获到SIGCHLD信号后要调用wait函数回收子进程，否则子进程会成为僵尸进程
    wait(NULL);
}

void out(int num)
{
    int i = 0;
    while (i < num) {
        printf("pid: %d running %d\n", getpid(), i++);
        sleep(2);
    }
}

int main(void)
{
    if (signal(SIGCHLD, sig_handler) == SIG_ERR) {
        perror("signal sigchld error");
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) { //parent process
        out(100);
    } else { //child process
        out(10);
    }

    return 0;
}
