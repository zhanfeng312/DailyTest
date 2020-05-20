#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGTSTP) {
        printf("SIGTSTP occured!\n");
    }
}

int main(void)
{
    if (signal(SIGTSTP, sig_handler) == SIG_ERR) {
        perror("signal sigtstp error");
    }

    printf("begin main running\n");

    raise(SIGTSTP);

    int i = 0;
    while (i < 20) {
        sleep(1);
        i++;
    }

    return 0;
}
