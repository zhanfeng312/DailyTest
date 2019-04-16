#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main (void) {
	int fd = open ("seek.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	const char* text = "Hello, World !";
	if (write (fd, text, strlen (text) * sizeof (text[0])) == -1) {
		perror ("write");
		return -1;
	}

	if (lseek (fd, -7, SEEK_CUR) == -1) {
		perror ("lseek");
		return -1;
	}

	off_t pos = lseek (fd, 0, SEEK_CUR);
	if (pos == -1) {
		perror ("lseek");
		return -1;
	}

	printf ("当前文件位置：%d\n", pos);

	text = "Linux";
	if (write (fd, text, strlen (text) * sizeof (text[0])) == -1) {
		perror ("write");
		return -1;
	}

	if (lseek (fd, 8, SEEK_END) == -1) {
		perror ("lseek");
		return -1;
	}

	text = "<-这里有个洞洞！";
	if (write (fd, text, strlen (text) * sizeof (text[0])) == -1) {
		perror ("write");
		return -1;
	}

	off_t size = lseek (fd, 0, SEEK_END);
	if (size == -1) {
		perror ("lseek");
		return -1;
	}

	printf ("文件大小：%d字节\n", size);

	close (fd);

	return 0;
}
