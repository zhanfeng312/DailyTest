#include <stdio.h>
#include <string.h>
#include <pthread.h>

unsigned int g_cn = 0;

void* thread_proc (void* arg) {
	unsigned int i;
	for (i = 0; i < 100000000; i++)
		++g_cn;

	return NULL;
}

int main (void) {
	size_t i;
	pthread_t tids[2];
	int error;

	for (i = 0; i < sizeof (tids) / sizeof (tids[0]); i++)
		if ((error = pthread_create (&tids[i], NULL, thread_proc,
			NULL)) != 0) {
			fprintf (stderr, "pthread_create: %s\n", strerror (error));
			return -1;
		}

	for (i = 0; i < sizeof (tids) / sizeof (tids[0]); i++)
		if ((error = pthread_join (tids[i], NULL)) != 0) {
			fprintf (stderr, "pthread_join: %s\n", strerror (error));
			return -1;
		}

	printf ("g_cn = %u\n", g_cn);

	return 0;
}
