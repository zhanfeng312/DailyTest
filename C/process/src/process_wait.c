#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>

void out_status(int status)
{
    if (WIFEXITED(status)) {
        printf("normal exit:%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal term:%d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("stopped sig:%d\n", WSTOPSIG(status));
    } else {
        printf("unknow sig\n");
    }
}

int main(void)
{
    int status;
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) { //子进程
        printf("child process: pid: %d, ppid:%d\n", getpid(), getppid());
        exit(3); //子进程终止运行
    }
    printf("parent process: pid: %d\n", getpid());
    printf("parent tid: %ld\n", syscall(__NR_gettid));
    //父进程调用wait函数阻塞，等待子进程结束并回收
    wait(&status);
    out_status(status);
    (void)pause();

#if 0
    printf("-------------------\n");

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("pid: %d, ppid:%d\n", getpid(), getppid());
        int i = 2, j = 0;
        int k = i / j;
        printf("k:%d\n", k);
    }
    wait(&status);
    out_status(status);

    /* 如果终止之前是否暂停过，要用waitpid函数 */
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("pid: %d, ppid:%d\n", getpid(), getppid());
        pause();
    }

    do {
        pid = waitpid(pid, &status, WNOHANG | WUNTRACED); //非阻塞版本
        if (pid == 0) {
            sleep(1);
        }
    } while(pid == 0);

    //wait(&status);
#endif

    out_status(status);
}