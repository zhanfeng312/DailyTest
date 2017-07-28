#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PAI 3.14159

void* thread_area (void* arg) {
	double r = *(double*)arg;
	double* s = malloc (sizeof (double));
//	exit (0);
	*s = PAI * r * r;
	pthread_exit (s); // <==> return s;
	*s = 2 * PAI * r;
	return s;
}

int main (void) {
	printf ("r = ");
	double r;
	scanf ("%lf", &r);

	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_area, &r);
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	double* s;
	if ((error = pthread_join (tid, (void**)&s)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	printf ("s = %g\n", *s);
	free (s);

	return 0;
}
