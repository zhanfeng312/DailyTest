#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t g_main;

void* ismain (void* arg) {
//	if (pthread_self () == g_main)
	if (pthread_equal (pthread_self (), g_main))
		printf ("我是主线程！\n");
	else
		printf ("我不是主线程！\n");

	return NULL;
}

int main (void) {
	g_main = pthread_self ();

	ismain (NULL);

	pthread_t tid;
	int error = pthread_create (&tid, NULL, ismain, NULL);
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	return 0;
}
