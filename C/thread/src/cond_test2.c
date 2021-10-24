#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t condLock;
} Test;

static Test g_test = {
    .cond = PTHREAD_COND_INITIALIZER,
    .condLock = PTHREAD_MUTEX_INITIALIZER
};

static int32_t CommonHandler(time_t second)
{
    int32_t ret;
    struct timespec ts;
    memset(&ts, 0, sizeof(ts));
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += second;
    pthread_mutex_lock(&g_test.condLock);
    ret = pthread_cond_timedwait(&g_test.cond, &g_test.condLock, &ts);
    pthread_mutex_unlock(&g_test.condLock);
    if (ret == ETIMEDOUT) {
        printf("timedout\n");
    }
    return ret;
}

static void *thread_func1(void *arg)
{
    printf("enter thread_func1!\n");
    int32_t ret = CommonHandler(5);
    printf("thread_func1 ret = %d\n", ret);

    return NULL;
}

static void *thread_func2(void *arg)
{
    printf("enter thread_func2!\n");
    int32_t ret = CommonHandler(10);
    printf("thread_func2 ret = %d\n", ret);

    return NULL;
}

static void *thread_func3(void *arg)
{
    printf("enter thread_func3!\n");
    sleep(2);
    // printf("call pthread_cond_signal.\n");
    // pthread_cond_signal(&g_test.cond);
    printf("call pthread_cond_broadcast.\n");
    pthread_cond_broadcast(&g_test.cond);

    return NULL;
}

int main(void)
{
    pthread_t threadId1;
    int32_t ret = pthread_create(&threadId1, NULL, thread_func1, NULL);
    if (ret != 0) {
        printf("pthread_create failed.\n");
        exit(1);
    }
    pthread_t threadId2;
    ret = pthread_create(&threadId2, NULL, thread_func2, NULL);
    if (ret != 0) {
        printf("pthread_create failed.\n");
        exit(1);
    }
    pthread_t threadId3;
    ret = pthread_create(&threadId3, NULL, thread_func3, NULL);
    if (ret != 0) {
        printf("pthread_create failed.\n");
        exit(1);
    }

    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);
    pthread_join(threadId3, NULL);

    return 0;
}