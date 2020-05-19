#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char *cmd1 = "ls";      //相对路径
const char *cmd2 = "/bin/ls"; //绝对路径

const char *argv1 = "-al";

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        //子进程调用exec函数执行新的程序
        //错误的，cmd1必须是绝对路径
        //if (execl(cmd1, cmd1, argv1, NULL) < 0) { //出错返回-1
        if (execl(cmd2, cmd1, argv1, NULL) < 0) {
            perror("execl error");
            exit(1);
        }
    } else {
        //父进程
        wait(NULL); //wait(0);
    }
    printf("first exec over-----------------\n");

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        const char *argv[] = { cmd1, argv1, NULL };
        if (execv(cmd2, (char * const*)argv) < 0) {
            perror("execv error");
            exit(1);
        }
    } else {
        wait(NULL);
    }
    printf("second exec over-----------------\n");

    return 0;
}
