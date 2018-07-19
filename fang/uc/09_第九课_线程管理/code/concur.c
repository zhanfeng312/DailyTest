#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_proc (void* arg) {
	size_t i;
	for (i = 0; i < 500; i++) {
		printf ("%*d\n", ((size_t)arg + 1) * 4, i + 1);
		usleep (50000);
	}

	return NULL;
}

int main (void) {
	pthread_t tids[20];

	size_t i;
	for (i = 0; i < sizeof (tids) / sizeof (tids[0]); i++) {
		int error = pthread_create (&tids[i], NULL, thread_proc, (void*)i);
		if (error) {
			fprintf (stderr, "pthread_create: %s\n", strerror (error));
			return -1;
		}
	}

	for (i = 0; i < sizeof (tids) / sizeof (tids[0]); i++) {
		int error = pthread_join (tids[i], NULL);
		if (error) {
			fprintf (stderr, "pthread_join: %s\n", strerror (error));
			return -1;
		}
	}

	return 0;
}
