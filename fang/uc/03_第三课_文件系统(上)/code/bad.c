#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main (void) {
	const char* text = "Hello, World !";
	/*
	if (write (3, text, strlen (text)) == -1) {
		perror ("write");
		return -1;
	}
	*/
	if (close (STDOUT_FILENO) == -1) {
		perror ("close");
		return -1;
	}

	if (creat ("bad.txt", 0644) == -1) {
		perror ("creat");
		return -1;
	}

	printf ("%s", text);

	return 0;
}
