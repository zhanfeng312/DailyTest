#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int             res;
    int             is_wait;
    pthread_cond_t  cond; //��������
    pthread_mutex_t mutex;//������
}Result;

void *set_fn(void *arg)
{

    return (void*)0;
}

void *get_fn(void *arg)
{

    return (void*)0;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t cal, get;


    Result r;
    r.is_wait = 0;

    return 0;
}