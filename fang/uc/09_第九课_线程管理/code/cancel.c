#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void elapse (void) {
	size_t i;
	for (i = 0; i < 800000000; ++i);
}

void* thread_proc (void* arg) {
	/*
	int error = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
	if (error) {
		fprintf (stderr, "pthread_setcancelstate: %s\n", strerror (error));
		exit (EXIT_FAILURE);
	}
	*//*
	int error = pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	if (error) {
		fprintf (stderr, "pthread_setcanceltype: %s\n", strerror (error));
		exit (EXIT_FAILURE);
	}
	*/
	for (;;) {
		printf ("线程：子在川上曰，逝者如斯夫。\n");
		elapse ();
	}

	return NULL;
}

int main (void) {
	setbuf (stdout, NULL);
	printf ("按<回车>取消线程...\n");

	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_proc, NULL);
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	getchar ();

	if ((error = pthread_cancel (tid)) != 0) {
		fprintf (stderr, "pthread_cancel: %s\n", strerror (error));
		exit (EXIT_FAILURE);
	}

	printf ("已发送取消请求，等待线程终止...\n");

	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	printf ("线程已终止。\n");

	return 0;
}
