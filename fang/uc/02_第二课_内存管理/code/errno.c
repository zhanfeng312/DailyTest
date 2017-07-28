#include <stdio.h>
#include <errno.h>

int main (void) {
	FILE* fp = fopen ("none", "r");
	if (! fp) {
		printf ("fopen: %d\n", errno);
		printf ("fopen: %s\n", strerror (errno));
		printf ("fopen: %m\n");
		perror ("fopen");
		return -1;
	}

	fclose (fp);

	return 0;
}
