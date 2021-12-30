#include <signal.h>
#include <unistd.h>
#include <stdio.h>

//定义信号处理函数，signo表示信号值
void sig_handler(int signo)
{
    printf("pid: %d, signal %d occured\n", getpid(), signo);
}

int main(void)
{
    //向内核登记信号值以及信号处理函数
    if (signal(SIGINT, sig_handler) == SIG_ERR) {  //ctrl + c
        perror("signal sigint error");
    }

    int exist = kill(getpid(), 0); //判断该进程是否存在
    printf("process exist: %d\n", exist);

    int i = 0;
    while (i < 20) {
        printf("%d running %d\n", getpid(), i++);
        if (i == 10) {
            //kill(getpid(), SIGKILL); //把自己杀死
            kill(getpid(), SIGINT);
        }
        sleep(1);
    }
    return 0;
}