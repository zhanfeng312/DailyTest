#include <stdio.h>
#include <signal.h>

void Test(const sigset_t *set, int signo)
{
    if (sigismember(set, signo) == 1) {
        printf("signo(%d)在信号集中\n", signo);
    } else {
        printf("signo(%d)不在信号集中\n", signo);
    }
}

int main(void)
{
    sigset_t set;

    sigemptyset(&set);
    Test(&set, 2);
    Test(&set, 3);

    sigaddset(&set, 2);
    Test(&set, 2);
    Test(&set, 3);

    sigfillset(&set);
    Test(&set, 2);
    Test(&set, 3);

    sigdelset(&set, 3);
    Test(&set, 2);
    Test(&set, 3);

    return 0;
}