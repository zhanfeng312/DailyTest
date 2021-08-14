#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#define INVALID_RESULT (-1)

typedef struct {
    int8_t resultCode;
    bool isWake;
    pthread_cond_t cond;
    pthread_mutex_t condLock;
} Test;

static Test g_test = {
    .resultCode = INVALID_RESULT,
    .isWake = false,
    .cond = PTHREAD_COND_INITIALIZER,
    .condLock = PTHREAD_MUTEX_INITIALIZER
};

static void *thread_func(void *arg)
{
    printf("enter %s\n", __func__);

    (void)pthread_mutex_lock(&g_test.condLock);
    g_test.resultCode = 10;
    g_test.isWake = true;
    (void)pthread_cond_signal(&g_test.cond);
    (void)pthread_mutex_unlock(&g_test.condLock);
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    int32_t ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret != 0) {
        printf("pthread_create failed.");
        return -1;
    }

    (void)pthread_mutex_lock(&g_test.condLock);
    while (!g_test.isWake) {
        ret = pthread_cond_wait(&g_test.cond, &g_test.condLock);
        printf("pthread_cond_wait = %d\n", ret);
    }
    (void)pthread_mutex_unlock(&g_test.condLock);

    (void)printf("The resultCode is %d\n", g_test.resultCode);

    (void)pthread_cond_destroy(&g_test.cond);
    (void)pthread_mutex_destroy(&g_test.condLock);
    return 0;
}