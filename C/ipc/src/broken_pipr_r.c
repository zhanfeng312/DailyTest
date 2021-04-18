#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    不完整管道：读取一个写端已经关闭的管道
*/
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
    } else if (pid > 0){ //parent process
        //父进程从不完整管道中读取数据
        sleep(5);
        close(fd[1]);

        while (1) {
            char c;
            if (read(fd[0], &c, 1) == 0) {
                printf("\nwrite-end of pipe closed\n");
                break;
            } else {
                printf("%c", c);
            }
        }
        close(fd[0]);
        wait(0); //防止产生僵尸进程
    } else { //child process
        //子进程负责将数据写入管道
        close(fd[0]);
        char *s = "123456789";
        write(fd[1], s, strlen(s) + 1);
        //写入数据后关闭管道的写端
        close(fd[1]);
    }
    return 0;
}