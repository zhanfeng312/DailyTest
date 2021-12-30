#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static void sig_handler(int signo)
{
    printf("Received signal(%d)\n", signo);
    int i = 0;
    while (i < 5) {
        printf("signal(%d) = %d\n", signo, ++i);
        sleep(1);
    }
}

int main(void)
{
    printf("Current pid is %d\n", getpid());

    //注册信号的第一种方式
    // signal(SIGINT, sig_handler);

    //注册信号的第二种方式
    //默认方式: 当函数被信号打断，函数会失败，并且errno置为EINTR, 如果设置了sa_flags为SA_RESTART, 当信号处理函数///执行完，该函数会重启, 继续等待
/*
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
*/
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("Please input s str:");
    char str[100];
    scanf("%s", str);
    printf("The str is %s\n", str);
}