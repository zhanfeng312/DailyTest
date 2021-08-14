#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* 利用信号量实现同步功能 */

//定义线程信号量
static sem_t sem1;
static sem_t sem2;

void *a_fn(void *arg)
{
	printf("thread a running!\n");
	sem_post(&sem1);
	return NULL;
}

void *b_fn(void *arg)
{
    sem_wait(&sem1);
	printf("thread b running!\n");
	sem_post(&sem2);
	return NULL;
}

void *c_fn(void *arg)
{
	sem_wait(&sem2);
	printf("thread c running!\n");
	return NULL;
}

int main(void)
{
	//线程信号量初始化，初值为0
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);

	pthread_t a, b, c;
	int err;
	if ((err = pthread_create(&a, NULL, a_fn, NULL)) != 0) {
		perror("pthread create error");
	}
	if ((err = pthread_create(&b, NULL, b_fn, NULL)) != 0) {
		perror("pthread create error");
	}
	if ((err = pthread_create(&c, NULL, c_fn, NULL)) != 0) {
		perror("pthread create error");
	}
	pthread_join(a, NULL);
	pthread_join(b, NULL);
	pthread_join(c, NULL);

	//销毁线程信号量
	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return 0;
}
