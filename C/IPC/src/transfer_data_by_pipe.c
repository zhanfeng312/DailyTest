#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int i = 0;
    pid_t pid;
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    //if ((pid = fork()) < 0) {
    //    perror("fork error");
    //    exit(1);
    //}
    //else if (pid == 0) { //child process

    //    close(fd[0]);

    //    char *s = "123";
    //    int len = strlen(s) * sizeof(char);
    //    if (write(fd[1], s, len) < 0) {
    //        perror("write error");
    //        exit(1);
    //    }

    //    close(fd[1]);
    //}
    //else {//parent process

    //    close(fd[1]);

    //    char buf[100] = { 0 };
    //    if (read(fd[0], buf, sizeof(buf)) < 0){
    //        perror("read error");
    //        exit(1);
    //    }

    //    printf("receive the buf is %s\n", buf);
    //    close(fd[0]);
    //    wait(0);
    //}

    //进程扇
    for (; i < 2; i++) {

        if ((pid = fork()) < 0) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) {//child process

            if (i == 0) {

                close(fd[0]);//关闭读端

                int start = 10, end = 100;
                if (write(fd[1], &start, sizeof(int)) != sizeof(int)) {
                    perror("write error");
                    exit(1);
                }
                if (write(fd[1], &end, sizeof(int)) < 0) {
                    perror("write error");
                    exit(1);
                }

                close(fd[1]);
                break;
            }

            if (i == 1) {

                close(fd[1]);//关闭写端

                int start, end;
                if (read(fd[0], &start, sizeof(int)) != sizeof(int)) {
                    perror("read error");
                    exit(1);
                }
                if (read(fd[0], &end, sizeof(int)) < 0) {
                    perror("read error");
                    exit(1);
                }

                printf("start: %d, end: %d\n", start, end);
                close(fd[0]);
                break;
            }
        }
        else {//parent process

            if (i == 1) {//当进程创建成功后，等待回收资源

                close(fd[0]);
                close(fd[1]);
                wait(0);
                wait(0);
            }
        }
    }

    exit(0);
}
