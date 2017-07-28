#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (void) {
//	mode_t old = umask (0333);
	mode_t old = umask (
		S_IWUSR | S_IXUSR |
		S_IWGRP | S_IXGRP |
		S_IWOTH | S_IXOTH);

	int fd = open ("umask.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	close (fd);
	umask (old);

	return 0;
}
