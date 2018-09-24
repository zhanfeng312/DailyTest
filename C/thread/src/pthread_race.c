#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//定义线程运行函数
void *th_fn(void *arg)
{
    int distance = (int)arg;
    int i;
    for (i = 1; i <= distance; i++) {
        printf("0x%lx run %d\n", pthread_self(), i);
        int time = (int)(drand48() * 100000);
        usleep(time); //微妙
    }
    return (void*)0;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t rabbit, turtle; //定义线程标识符

    //创建rabbit线程
    if ((err = pthread_create(&rabbit, NULL, th_fn, (void*)50)) != 0) {
        perror("pthread_create error");
    }
    //创建turtle线程
    if ((err = pthread_create(&turtle, NULL, th_fn, (void*)50)) != 0) {
        perror("pthread_create error");
    }

    //sleep(10);

    //主控线程调用pthread_join()，自己会阻塞
    //直到rabbit和turtle线程结束方可运行
    pthread_join(rabbit, NULL);
    pthread_join(turtle, NULL);

    printf("control thread id: 0x%lx\n", pthread_self());
    printf("finished!\n");

    return 0;
}