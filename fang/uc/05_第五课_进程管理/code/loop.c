#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	int i;
	for (i = 0; i < 3; i++) {
		pid_t pid = fork ();
		if (pid == -1) {
			perror ("fork");
			return -1;
		}

		if (pid == 0) {
			printf ("子进程：我是%u进程。我要退出了。\n", getpid ());
			return 0;
		}
	}

	for (;;) {
		printf ("父进程：我要等待子进程...\n");

		pid_t pid = wait (0);
		if (pid == -1) {
			if (errno != ECHILD) {
				perror ("wait");
				return -1;
			}

			printf ("父进程：已经没有子进程可等了，走喽！\n");
			break;
		}

		printf ("父进程：发现%u进程退出了。\n", pid);
	}

	return 0;
}
