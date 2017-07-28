#include <stdio.h>
#include <stdlib.h>

int main (void) {
	int* p1 = malloc (sizeof (int));
	int* p2 = malloc (sizeof (int));
	printf ("%p, %p\n", p1, p2);

	free (p2);

	p1[3] = 0;
	free (p1);

	return 0;
}
