#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf ("    进程ID：%u\n", getpid ());
	printf ("  父进程ID：%u\n", getppid ());
	printf ("实际用户ID：%u\n", getuid ());
	printf ("有效用户ID：%u\n", geteuid ());
	printf ("  实际组ID：%u\n", getgid ());
	printf ("  有效组ID：%u\n", getegid ());

	return 0;
}
