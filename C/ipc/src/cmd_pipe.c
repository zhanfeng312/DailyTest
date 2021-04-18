#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};

int main(void)
{
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    int i = 0;
    pid_t pid;
    for(; i < 2; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) { //child process

            if (i == 0) {
                //第一个子进程，负责往管道写入数据
                //关闭读端
                close(fd[0]);

                //将标准输出重定向到管道的写端
                //文件描述符的复制（指针的复制）
                if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                    perror("dup2 error");
                    exit(1);
                }
                close(fd[1]);

                //调用exec函数执行cat命令
                if (execvp(cmd1[0], cmd1) < 0) { //命令路径，参数列表, 相对、绝对路径都可以
                    perror("execvp error");
                    exit(1);
                }
                break;
            }
            if (i == 1) {
                //第二个子进程，负责从管道读取数据
                //关闭写端
                close(fd[1]);

                //将标准输入重定向到管道的读端
                if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                    perror("dup2 error");
                    exit(1);
                }
                close(fd[0]);

                //调用exec函数执行grep命令
                if (execvp(cmd2[0], cmd2) < 0) { //命令路径，参数列表, 相对、绝对路径都可以
                    perror("execvp error");
                    exit(1);
                }
                break;
            }
        } else { //parent process
            if (i == 1) {
                //父进程要等到子进程全部创建完毕才去回收
                close(fd[0]);
                close(fd[1]);
                wait(0);
                wait(0);
            }
        }
    }

    return 0;
}