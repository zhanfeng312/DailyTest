#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    if ((pid = vfork()) < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid == 0) { //子进程
        //子进程调用exec函数执行新的程序
        if (execl("/bin/ls", "ls", "-al", NULL) < 0) {
            perror("execl error");
            exit(-1);
        }
    } else { //父进程
        wait(NULL); //wait(0);
    }

    return 0;
}
