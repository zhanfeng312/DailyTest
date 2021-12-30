#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int g_v[10];
int *h_v = NULL;

void Print(int *array, int arraySize)
{
    int i = 0;
    for(; i < arraySize; i++) {
        if (i == 0) {
            printf("%d", array[i]);
        } else {
            printf(",%d", array[i]);
        }
    }
    printf("\n");
}

void set(int val)
{
    int a_v[10];
    int i = 0;
    for(; i < 10; i++) {
        a_v[i] = val;
        g_v[i] = val;
        h_v[i] = val;
        sleep(1);
    }
    printf("g_v:");
    Print(g_v, 10);

    printf("h_v:");
    Print(h_v, 10);

    printf("a_v:");
    Print(a_v, 10);
}

void sig_handler(int signo)
{
    if (signo == SIGTSTP) {
        printf("SIGTSTP occured\n");
        set(20);
        printf("end SIGTSTP\n");
    }
}

int main(void)
{
    /* 当信号到达后, 当前的操作会被中断, 信号处理函数执行完，再返回上次的中断点继续执行 */
    if (signal(SIGTSTP, sig_handler) == SIG_ERR) {
        perror("signal sigtstp error");
    }

    h_v = (int *)calloc(10, sizeof(int));
    if (h_v == NULL) {
        return -1;
    }

    printf("begin main running\n");
    set(10);
    printf("end main running\n");

    free(h_v);

    return 0;
}
