#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf ("进程ID：%u\n", getpid ());
	return 0;
}
