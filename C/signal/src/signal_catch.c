#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

//定义信号处理函数, signo表示信号值
void sig_handler(int signo)
{
    printf("pid: %d, signal %d occured\n", getpid(), signo);
}

int main(void)
{
    /*
        向内核登记信号值以及信号处理函数
        忽略此信号时, 第二个参数传"SIG_IGN
    */
    if (signal(SIGTSTP, sig_handler) == SIG_ERR) { //ctrl + z
        perror("signal sigtstp error");
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {  //ctrl + c
        perror("signal sigint error");
    }

    /*
        SIGKILL, SIGSTOP不能被忽略, 也不能被捕获
    */
    if (signal(SIGKILL, sig_handler) == SIG_ERR) {
        perror("signal sigkill error");
    }
    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
        perror("signal sigstop error");
    }

    if (signal(SIGKILL, SIG_IGN) == SIG_ERR) {
        perror("ingore signal sigkill error");
    }
    if (signal(SIGSTOP, SIG_IGN) == SIG_ERR) {
        perror("ignore signal sigstop error");
    }

    while (1) {
        sleep(5);
    }
    return 0;
}