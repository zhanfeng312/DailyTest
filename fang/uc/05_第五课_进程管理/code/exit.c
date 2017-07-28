#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void doexit1 (void) {
	printf ("doexit1()...\n");
}

void doexit2 (int status, void* arg) {
	printf ("doexit2(%d,%s)...\n", status, (char*)arg);
}

int foo (void) {
	printf ("foo()...\n");

//	exit (EXIT_SUCCESS);
//	exit (EXIT_FAILURE);
	exit (1234);
//	_exit (1234);
//	_Exit (1234);

	return 10;
}

int main (void) {
	if (atexit (doexit1) == -1) {
		perror ("atexit");
		return -1;
	}

	if (on_exit (doexit2, "再见") == -1) {
		perror ("on_exit");
		return -1;
	}

//	printf ("foo()函数返回%d。\n", foo ());

	return 1234;
}
