#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
    int8_t resultCode;
    pthread_cond_t cond;
    pthread_mutex_t condLock;
} Test;

static Test g_test;

static void *thread_func(void *arg)
{
    printf("start sleep\n");
    sleep(5);
    printf("stop sleep\n");
    g_test.resultCode = 10;
    pthread_cond_signal(&g_test.cond);
}

static void *thread_func1(void *arg)
{
    printf("start sleep\n");
    sleep(5);
    printf("stop sleep\n");
    g_test.resultCode = 5;
    pthread_cond_signal(&g_test.cond);
}

int main()
{
    pthread_cond_init(&g_test.cond, NULL);
    pthread_mutex_init(&g_test.condLock, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    pthread_cond_wait(&g_test.cond, &g_test.condLock);
    printf("resultCode is %d\n", g_test.resultCode);

    pthread_create(&tid, NULL, thread_func1, NULL);

    pthread_cond_wait(&g_test.cond, &g_test.condLock);
    printf("resultCode is %d\n", g_test.resultCode);

    pthread_cond_destroy(&g_test.cond);
    pthread_mutex_destroy(&g_test.condLock);
    return 0;
}