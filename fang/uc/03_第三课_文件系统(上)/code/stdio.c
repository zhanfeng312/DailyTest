#include <stdio.h>

int main (void) {
	FILE* fp = fopen ("stdio.dat", "wb");
	if (! fp) {
		perror ("fopen");
		return -1;
	}

	unsigned int i;
	for (i = 0; i < 100000; i++)
		fwrite (&i, sizeof (i), 1, fp);

	fclose (fp);

	return 0;
}
