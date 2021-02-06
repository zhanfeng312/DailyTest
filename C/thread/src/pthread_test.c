#include <stdio.h>
#include <pthread.h>

typedef struct {
    int result;
    pthread_mutex_t resultLock;
} MyStruct;

static MyStruct myStruct = {
    .result = 0,
    .resultLock = PTHREAD_MUTEX_INITIALIZER
};

void *th_func1(void *arg)
{
    int i = 1;
    for (; i <= 10000; i++) {
        pthread_mutex_lock(&myStruct.resultLock);
        myStruct.result++;
        pthread_mutex_unlock(&myStruct.resultLock);
    }
    return (void*)0;
}

void *th_func2(void *arg)
{
    int i = 1;
    for (; i <= 10000; i++) {
        pthread_mutex_lock(&myStruct.resultLock);
        myStruct.result++;
        pthread_mutex_unlock(&myStruct.resultLock);
    }
    return (void*)0;
}

int main(void)
{
    pthread_t th1, th2;
    int ret;
    if ((ret = pthread_create(&th1, NULL, th_func1, NULL)) < 0) {
        perror("pthread_create error");
    }
    if ((ret = pthread_create(&th2, NULL, th_func2, NULL)) < 0) {
        perror("pthread_create error");
    }
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("The sum is %d\n", myStruct.result);
    return 0;
}