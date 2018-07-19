#include <stdio.h>
#include <errno.h>

int main (void) {
	FILE* fp = fopen ("none", "r");
	fp = fopen ("/etc/passwd", "r");
	if (errno) {
		perror ("fopen");
		printf ("fp = %p\n", fp);
		return -1;
	}

	fclose (fp);

	return 0;
}
