#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

int main (void) {
	const char* text = "Hello, World !";
	size_t size = (strlen (text) + 1) * sizeof (text[0]);

	int fd = open ("trunc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (ftruncate (fd, size) == -1) {
		perror ("ftruncate");
		return -1;
	}

	void* map = mmap (NULL, size, PROT_READ | PROT_WRITE, 
		MAP_SHARED/*MAP_PRIVATE*/, fd, 0);
	if (map == MAP_FAILED) {
		perror ("mmap");
		return -1;
	}

	memcpy (map, text, size);
	printf ("%s\n", map);

	munmap (map, size);
	close (fd);

	return 0;
}
