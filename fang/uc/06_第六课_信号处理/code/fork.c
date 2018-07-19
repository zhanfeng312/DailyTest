#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint (int signum) {
	printf ("%u进程：收到SIGINT信号！\n", getpid ());
}

int main (void) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	if (signal (SIGQUIT, SIG_IGN) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		printf ("%u进程：我是子进程，正在运行...\n", getpid ());
		for (;;);
		return 0;
	}

	sleep (1);
	printf ("%u进程：我是父进程，即将退出。\n", getpid ());

	return 0;
}
