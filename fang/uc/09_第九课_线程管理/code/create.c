#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_proc (void* arg) {
	printf ("%lu线程：%s\n", pthread_self (), (char*)arg);
	return NULL;
}

int main (void) {
	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_proc,
		"我是快乐的子线程！");
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	printf ("%lu线程：我是主线程，创建了%lu线程。\n", pthread_self (),
		tid);

	sleep (1);

	return 0;
}
