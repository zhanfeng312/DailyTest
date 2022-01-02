#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void out_status(int status)
{
    if (WIFEXITED(status)) { //如果正常终止
        printf("Child process exited value: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) { //如果被信号打断
        printf("Child process terminate due signal: %d\n", WTERMSIG(status));
    } else { //其它退出类型
        printf("Child process other exit type\n");
    }
}

int main(void)
{
    int status;
    pid_t pid = fork();
    pid_t wpid;
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) { //子进程
        printf("child process: pid: %d, ppid:%d\n", getpid(), getppid());
        sleep(3);
        //exit(3); //子进程终止运行
        return 3;
    }
    printf("parent process: pid: %d\n", getpid());

    wpid = wait(&status);
    if (wpid == -1) {
        perror("wait error");
        exit(1);
    }
    out_status(status);

    return 0;
}