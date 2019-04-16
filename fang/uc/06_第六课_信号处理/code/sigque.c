#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void siginfo (int signum, siginfo_t* si, void* pv) {
	printf ("%u进程：收到发自%u进程的%d信号(附加值=%d)！\n",
		getpid(), si -> si_pid, signum, si -> si_value.sival_int);
	usleep (100);
}

int main (void) {
	int signum = 50;
//	int signum = SIGINT;

	struct sigaction act = {};
	act.sa_sigaction = siginfo;
	act.sa_flags = SA_SIGINFO | SA_RESTART;

	if (sigaction (signum, &act, NULL) == -1) {
		perror ("sigaction");
		return -1;
	}

	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		pid_t ppid = getppid ();

		int i;
		for (i = 0; i < 10; i++) {
			sigval_t sv;
			sv.sival_int = i;
			printf ("%u进程：向%u进程发送%d信号(附加值=%d)...\n",
				getpid (), ppid, signum, sv.sival_int);
			if (sigqueue (ppid, signum, sv) == -1) {
				perror ("sigqueue");
				return -1;
			}
		}

		printf ("%u进程：我即将退出。\n", getpid ());

		return 0;
	}

	if ((pid = wait (0)) == -1) {
		perror ("wait");
		return -1;
	}

	printf ("%u进程：%u进程已退出。\n", getpid (), pid);

	return 0;
}
