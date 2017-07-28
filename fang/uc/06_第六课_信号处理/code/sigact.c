#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint1 (int signum) {
	printf ("收到SIGINT信号！睡眠中...\n");
	sleep (5);
	printf ("睡醒了。\n");
}

void sigint2 (int signum, siginfo_t* si, void* pv) {
	printf ("收到发自%u进程的SIGINT信号！\n", si -> si_pid);
}

int main (void) {
	printf ("按<Ctrl+C>和<Ctrl+\\>看效果...\n");

	struct sigaction act = {};

	printf ("睡眠中只屏蔽SIGINT，不屏蔽SIGQUIT。\n");
	act.sa_handler = sigint1;
	/*
	printf ("睡眠中既屏蔽SIGINT，也屏蔽SIGQUIT。\n");
	act.sa_handler = sigint1;
	sigemptyset (&act.sa_mask);
	sigaddset (&act.sa_mask, SIGQUIT);
	*//*
	printf ("睡眠中既不屏蔽SIGINT，也不屏蔽SIGQUIT。\n");
	act.sa_handler = sigint1;
	act.sa_flags = SA_NOMASK;
	*//*
	printf ("睡眠中不屏蔽SIGINT，只屏蔽SIGQUIT。\n");
	act.sa_handler = sigint1;
	sigemptyset (&act.sa_mask);
	sigaddset (&act.sa_mask, SIGQUIT);
	act.sa_flags = SA_NOMASK;
	*//*
	printf ("附带更多信号信息。\n");
	act.sa_sigaction = sigint2;
	act.sa_flags = SA_SIGINFO;
	*//*
	printf ("一次性信号处理。\n");
	act.sa_handler = sigint1;
	act.sa_flags = SA_RESETHAND;
	*/
	if (sigaction (SIGINT, &act, NULL) == -1) {
		perror ("sigaction");
		return -1;
	}

	for (;;)
		pause ();

	return 0;
}
