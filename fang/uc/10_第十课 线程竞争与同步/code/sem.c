#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

unsigned int g_cn = 0;

sem_t g_sem;

void* thread_proc (void* arg) {
	unsigned int i;
	for (i = 0; i < 100000000; i++) {
		sem_wait (&g_sem);
		g_cn++;
		sem_post (&g_sem);
	}

	return NULL;
}
	
int main (void) {
	size_t i;
	pthread_t tids[2];
	int error;

	sem_init (&g_sem, 0, 1);

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

	sem_destroy (&g_sem);

	printf ("g_cn = %u\n", g_cn);

	return 0;
}
