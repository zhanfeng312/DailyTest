#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGALRM) {
        system("clear");
        time_t t = time(NULL);
        struct tm *timeInfo = localtime(&t);
        printf("%02d:%02d:%02d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
        alarm(1);
    }
}

int main(void)
{
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        perror("signal sigalrm error");
    }

    int ret = alarm(5);
    ret = alarm(0);
    printf("ret is %d\n", ret);

    while (1) {
        pause();
    }

    return 0;

}
