#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void sigalrm (int signum) {
	time_t t = time (NULL);
	struct tm* lt = localtime (&t);

	printf ("\r%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);

	alarm (1);
}

int main (void) {
	setbuf (stdout, NULL);

	if (signal (SIGALRM, sigalrm) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	sigalrm (SIGALRM);

	for (;;);

	return 0;
}
