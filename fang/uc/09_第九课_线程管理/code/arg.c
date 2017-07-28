#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define PAI 3.14159

void* thread_area (void* arg) {
	double r = *(double*)arg;
	*(double*)arg = PAI * r * r;
	return NULL;
}

typedef struct tag_Pyth {
	double a;
	double b;
	double c;
}	PYTH, *LPPYTH;

void* thread_pyth (void* arg) {
	LPPYTH pyth = (LPPYTH)arg;
	pyth -> c = sqrt (pyth -> a * pyth -> a + pyth -> b * pyth -> b);
	return NULL;
}

void* thread_aver (void* arg) {
	double* d = (double*)arg;
	d[2] = (d[0] + d[1]) / 2;
	return NULL;
}

void* thread_show (void* arg) {
	sleep (1);
	printf ("n = %d\n", *(int*)arg);
	return NULL;
}

int main (void) {
	printf ("r = ");
	double rs;
	scanf ("%lf", &rs);

	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_area, &rs);
	if (error) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	printf ("s = %g\n", rs);

	PYTH pyth;
	printf ("a = ");
	scanf ("%lf", &pyth.a);
	printf ("b = ");
	scanf ("%lf", &pyth.b);

	if ((error = pthread_create (&tid, NULL, thread_pyth, &pyth)) != 0) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	printf ("c = %g\n", pyth.c);

	double d[3];
	printf ("x = ");
	scanf ("%lf", &d[0]);
	printf ("y = ");
	scanf ("%lf", &d[1]);

	if ((error = pthread_create (&tid, NULL, thread_aver, d)) != 0) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	printf ("z = %g\n", d[2]);

	int* n = malloc (sizeof (int));
	*n = 1234;

	if ((error = pthread_create (&tid, NULL, thread_show, n)) != 0) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}
	/*
	free (n);
	*/
	if ((error = pthread_join (tid, NULL)) != 0) {
		fprintf (stderr, "pthread_join: %s\n", strerror (error));
		return -1;
	}

	free (n);

	return 0;
}
