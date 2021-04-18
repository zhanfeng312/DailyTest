#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

/*
    不完整管道：写一个读端已经被关闭的管道
*/
void sig_handler(int signo)
{
    if (signo == SIGPIPE) {
        printf("SIGPIPE occured\n");
    }
}

int main(void)
{
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) {//parent process
        //父进程负责将数据写入到不完整管道（读端关闭）
        sleep(5);
        close(fd[0]);
        if (signal(SIGPIPE, sig_handler) == SIG_ERR) {
            perror("signal error");
            exit(1);
        }
        char *s = "1234";
        int writeNum = strlen(s) + 1;
        if (write(fd[1], s, writeNum) != writeNum) {
            fprintf(stderr, "%s, %s\n", strerror(errno), (errno == EPIPE) ? "EPIPE" : "unkonwn");
        }
        close(fd[1]);
        wait(0);
    } else {//child process
        close(fd[0]);//子进程关闭管道的读端
        close(fd[1]);
    }
    return 0;
}