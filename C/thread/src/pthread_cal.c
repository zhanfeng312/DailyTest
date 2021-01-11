#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int             res;
    int             is_wait;
    pthread_cond_t  cond;  //条件变量
    pthread_mutex_t mutex; //互斥锁
}Result;

//定义计算结果的线程
void *set_fn(void *arg)
{
	sleep(5);
	int i = 1, sum = 0;
	for(; i <= 100; i++){
		sum += i;
	}

	Result *r = (Result*)arg;
	r->res = sum;

	//对共享资源进行加锁
	pthread_mutex_lock(&r->mutex);

	while(!r->is_wait){
		pthread_mutex_unlock(&r->mutex);
		usleep(200);
		pthread_mutex_lock(&r->mutex);
	}
	pthread_mutex_unlock(&r->mutex);

	pthread_cond_broadcast(&r->cond);

    return (void*)0;
}

//定义获取结果的线程
void *get_fn(void *arg)
{
	//sleep(5);
	Result *r = (Result*)arg;

	//对共享资源进行加锁
	pthread_mutex_lock(&r->mutex);
	r->is_wait = 1;

	pthread_cond_wait(&r->cond, &r->mutex);
	//释放锁
	pthread_mutex_unlock(&r->mutex);

	int res = r->res;

	printf("0x%lx get the result is %d\n", pthread_self(), res);

    return (void*)0;
}

//主函数
int main(int argc, char *argv[])
{
    int err;
    pthread_t cal, get;

	Result r;
	r.is_wait = 0;

	//初始化条件变量和互斥锁
	pthread_cond_init(&r.cond, NULL);
	pthread_mutex_init(&r.mutex, NULL);

	if ((err = pthread_create(&get, NULL, get_fn, (void*)&r)) != 0){
		perror("pthread create error");
	}
	if ((err = pthread_create(&cal, NULL, set_fn, (void*)&r)) != 0){
		perror("pthread create error");
	}

	pthread_join(get, NULL);
	pthread_join(cal, NULL);

	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);

    return 0;
}
