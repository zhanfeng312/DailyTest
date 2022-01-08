#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
	char buf[128] = {0};
	int fd = open("a.txt", O_RDONLY);
	if (fd == -1) {
		perror("open errorn");
		exit(1);
	}

	while (1) {
		ssize_t size = read(fd, buf, sizeof(buf));
		if (size < 0) {
			perror("read error.");
			exit(1);
		} else if (size == 0) {
			printf("read finished\n");
			break;
		} else {
			printf("read the size is %ld\n", size);
			write(STDOUT_FILENO, buf, size);
		}
	}
}
