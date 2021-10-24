#include <stdio.h>
#include <pthread.h>

//static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_mutex;
static int g_num = 0;

/* 连续两次lock造成死锁 */
static void *ThreadFunc(void *arg)
{
    pthread_mutex_lock(&g_mutex);
    g_num += 10;
    pthread_mutex_lock(&g_mutex);
}

int main(int argc, char *argv[])
{
    pthread_mutex_init(&g_mutex, NULL); //默认属性

    pthread_t tid;
    pthread_create(&tid, NULL, ThreadFunc, NULL);

    pthread_join(tid, NULL);

    printf("g_num = %d!\n", g_num);

    pthread_mutex_destroy(&g_mutex);
    return 0;
}