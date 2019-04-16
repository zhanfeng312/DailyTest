#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE "/tmp/fifo"

int main (void) {
	printf ("打开管道...\n");

	int fd = open (FIFO_FILE, O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	printf ("接收数据...\n");

	for (;;) {
		char buf[1024];

		ssize_t rb = read (fd, buf, sizeof (buf));
		if (rb == -1) {
			perror ("read");
			return -1;
		}

		if (! rb)
			break;

		printf ("< %s\n", buf);
	}

	printf ("关闭管道...\n");

	if (close (fd) == -1) {
		perror ("close");
		return -1;
	}

	printf ("大功告成！\n");

	return 0;
}
