#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint (int signum) {
	printf ("%u进程：收到SIGINT信号，即将退出。\n", getpid ());
	exit (0);
}

int main (void) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	printf ("%u进程：向自己发送SIGINT信号...\n", getpid ());

	if (raise (SIGINT) == -1) {
		perror ("kill");
		return -1;
	}

	for (;;);

	return 0;
}
