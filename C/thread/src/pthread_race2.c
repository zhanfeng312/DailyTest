#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    char   name[20];
    int    time;
    int    start;
    int    end;
}RaceArg;


//定义线程运行函数
void *th_fn(void *arg)
{
    RaceArg *r = (RaceArg*)arg;
    int i = r->start;
    for (; i <= r->end; i++) {
        printf("%s(%lx) running %d\n", r->name, pthread_self(), i);
        usleep(r->time);
    }

    return (void*)0;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t rabbit, turtle;

    RaceArg r_a = {"rabbit", (int)(drand48()*10000000), 20, 50};

    RaceArg t_a = {"turtle", (int)(drand48()*10000000), 20, 60};

    //创建rabbit线程
    if ((err = pthread_create(&rabbit, NULL, th_fn, (void*)&r_a)) != 0) {
        perror("pthread_create error");
    }
    //创建turtle线程
    if ((err = pthread_create(&turtle, NULL, th_fn, (void*)&t_a)) != 0) {
        perror("pthread_create error");
    }

    pthread_join(rabbit, NULL);
    pthread_join(turtle, NULL);

    printf("control thread id: 0x%lx\n", pthread_self());
    printf("finished!\n");

    return 0;
}