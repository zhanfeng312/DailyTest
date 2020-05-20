#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sig_handler(int signo)
{
    if (signo == SIGALRM) {
        printf("clock time out\n");
        //重新设置定时器(周期性的定时)
        alarm(5);
    }
}

void out_data(void)
{
    int i = 1;
    while (i <= 20) {
        double d = drand48();
        printf("%-10d:%lf\n", i++, d);
        sleep(1);
    }
}

int main(void)
{
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        perror("signal sigalrm error");
    }

    //设置定时器
    alarm(5);

    printf("begin main running\n");
    out_data();
    printf("end main running\n");

    return 0;
}
