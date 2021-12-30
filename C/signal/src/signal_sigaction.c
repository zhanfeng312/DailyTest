#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

static void sig_handler(int signo)
{
    printf("Received signal(%d)\n", signo);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = sig_handler;
    int ret = sigaction(SIGINT, &sa, NULL);
    if (ret != 0) {
        perror("sigaction sigint failed.");
    }
    ret = sigaction(SIGKILL, &sa, NULL);
    if (ret != 0) {
        perror("sigaction sigkill failed.");
    }
    ret = sigaction(SIGSTOP, &sa, NULL);
    if (ret != 0) {
        perror("sigaction sigstop failed.");
    }

    sa.sa_handler = SIG_IGN;
    ret = sigaction(SIGKILL, &sa, NULL);
    if (ret != 0) {
        perror("sigaction sigkill failed.");
    }
    ret = sigaction(SIGSTOP, &sa, NULL);
    if (ret != 0) {
        perror("sigaction sigstop failed.");
    }

    while (1) {
        sleep(5);
    }

    return 0;
}