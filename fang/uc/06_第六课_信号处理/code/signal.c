#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint (int signum) {
	printf ("%u进程：收到SIGINT信号！\n", getpid ());
//	signal (SIGINT, SIG_DFL);
//	signal (SIGINT, sigint);
}

void sigkill (int signum) {
	printf ("%u进程：收到SIGKILL信号！\n", getpid ());
}

int main (void) {
	/*
	if (signal (SIGINT, SIG_IGN) == SIG_ERR) {
		perror ("signal");
		return -1;
	}
	*/
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}
	/*
	if (signal (SIGKILL, SIG_IGN) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	if (signal (SIGKILL, sigkill) == SIG_ERR) {
		perror ("signal");
		return -1;
	}
	*/
	printf ("%u进程：我在运行，按<Ctrl+C>没用，按<Ctrl+\\>终止...\n",
		getpid ());

	for (;;);

	return 0;
}
