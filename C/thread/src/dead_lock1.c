#include <stdio.h>
#include <pthread.h>

pthread_mutex_t g_mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex2 = PTHREAD_MUTEX_INITIALIZER;

static int g_num1 = 0;
static int g_num2 = 0;

/* 两线程互相依赖锁, 造成死锁 */
static void IncrementNum1(void)
{
    int i;
    for (i = 0; i < 100000; i++) {
        g_num1++;
    }
}

static void IncrementNum2(void)
{
    int i;
    for (i = 0; i < 100000; i++) {
        g_num2++;
    }
}

static void *th_func1(void *arg)
{
    pthread_mutex_lock(&g_mutex1);
    printf("th_func1 get lock1 ok\n");
    IncrementNum1();

    pthread_mutex_lock(&g_mutex2);
    printf("th_func1 get lock2 ok\n");
    IncrementNum2();

    pthread_mutex_unlock(&g_mutex2);
    pthread_mutex_unlock(&g_mutex1);
    return NULL;
}

static void *th_func2(void *arg)
{
    pthread_mutex_lock(&g_mutex2);
    printf("th_func2 get lock2 ok\n");
    IncrementNum2();

    pthread_mutex_lock(&g_mutex1);
    printf("th_func2 get lock1 ok\n");
    IncrementNum1();

    pthread_mutex_unlock(&g_mutex1);
    pthread_mutex_unlock(&g_mutex2);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, th_func1, NULL);
    pthread_create(&tid2, NULL, th_func2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("g_num1 = %d, g_num2 = %d\n", g_num1, g_num2);

    pthread_mutex_destroy(&g_mutex1);
    pthread_mutex_destroy(&g_mutex2);
    return 0;
}