#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg)
{
	int sleep_time = *((int*)arg);

	printf("sleep_time is %d\n", sleep_time);
	sleep(sleep_time);

	printf("thread over!\n");
}

int main(int argc, char *argv[])
{
	#define SLEEP_TIME  (10)
	int sleep_time = SLEEP_TIME;
	void *status = NULL;

	pthread_t tid;
	pthread_attr_t attr;

	int ret = pthread_attr_init(&attr);
	if (ret != 0)
	{
		printf("pthread_attr_init failed!\n");
		return ret;
	}
	
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (ret == 0)
	{
		pthread_create(&tid, NULL, thread_func, (void *)&sleep_time);
	}

	pthread_attr_destroy(&attr);

	sleep(1);
	printf("main thread over!\n");
	return 0;
}
