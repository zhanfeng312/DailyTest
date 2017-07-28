#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main (void) {
	int fd = open ("read.txt", O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	char text[256];
	size_t toread = sizeof (text);

	ssize_t readed = read (fd, text, toread);
	if (readed == -1) {
		perror ("read");
		return -1;
	}

	printf ("期望读取%d字节，实际读取%d字节。\n", toread, readed);
	text[readed / sizeof (text[0])] = '\0';
	printf ("读取内容：%s\n", text);

	close (fd);

	return 0;
}
