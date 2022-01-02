#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* 实现: ls | wc -l功能 */
int main(void)
{
    int fd[2];
    pid_t pid;

    int ret = pipe(fd); //创建管道并打开文件描述符
    if (ret == -1) {
        perror("pipe error.");
        exit(1);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork error.");
        exit(1);
    } else if (pid == 0) { //child process
        printf("I am child, pid = %u, ppid = %u\n", getpid(), getppid());
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", NULL);
        exit(1);
    }
    //parent process
    printf("I am parent, pid = %u\n", getpid());
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execlp("wc", "wc", "-l", NULL);
    return 0;
}
