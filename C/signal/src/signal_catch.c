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
#if 1
    //向内核登记信号处理函数以及信号值
    if (signal(SIGTSTP, sig_handler) == SIG_ERR) { //ctrl + z
        perror("signal sigtstp error");
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {  //ctrl + c
        perror("signal sigint error");
    }
#else
    //忽略SIGTSTP SIGINT信号
   if (signal(SIGTSTP, SIG_IGN) == SIG_ERR) { //ctrl + z
       perror("signal sigtstp error");
   }
   if (signal(SIGINT, SIG_IGN) == SIG_ERR) {  //ctrl + c
       perror("signal sigint error");
   }
#endif

    //用户自定义信号，默认动作：终止进程
    if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
        perror("signal sigusr1 error");
    }
    if (signal(SIGUSR2, sig_handler) == SIG_ERR) {
        perror("signal sigusr2 error");
    }

    //SIGKILL, SIGSTOP不能被忽略, 也不能被捕获，此时会报error
    if (signal(SIGKILL, sig_handler) == SIG_ERR) {
        perror("signal sigkill error");
    }
    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
        perror("signal sigstop error");
    }

    int i = 0;
    while (i < 20) {
        printf("%d running %d\n", getpid(), i++);
        sleep(1);
    }

    //向进程自己发送SIGUSR1 和 SIGUSR2信号
    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGUSR2);

    return 0;
}
