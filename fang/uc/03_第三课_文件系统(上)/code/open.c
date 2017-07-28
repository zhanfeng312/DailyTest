#include <stdio.h>
#include <fcntl.h>

int main (void) {
	int fd1 = open ("open.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd1 == -1) {
		perror ("open");
		return -1;
	}

	printf ("fd1 = %d\n", fd1);

	int fd2 = open ("open.txt", O_RDONLY);
	if (fd2 == -1) {
		perror ("open");
		return -1;
	}

	printf ("fd2 = %d\n", fd2);

	close (fd2);
	close (fd1);

	return 0;
}
