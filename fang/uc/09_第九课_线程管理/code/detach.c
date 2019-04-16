#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_proc (void* arg) {
	int i;
	for (i = 0; i < 200; i++) {
		putchar ('-');
		usleep (50000);
	}
	return NULL;
}

int main (void) {
	setbuf (stdout, NULL);

	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_proc, NULL);
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_detach (tid)) != 0) {
		fprintf (stderr, "pthread_detach: %s\n", strerror (error));
		return -1;
	}
	/*
	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}
	*/
	int i;
	for (i = 0; i < 200; i++) {
		putchar ('+');
		usleep (100000);
	}

	printf ("\n");

	return 0;
}
