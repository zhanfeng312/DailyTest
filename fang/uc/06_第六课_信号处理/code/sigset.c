#include <stdio.h>
#include <signal.h>

int main (void) {
	sigset_t set;
	printf ("%u\n", sizeof (set));

	sigfillset (&set);
	sigemptyset (&set);

	sigaddset (&set, SIGINT);
	sigaddset (&set, SIGQUIT);
	sigdelset (&set, SIGQUIT);

	if (sigismember (&set, SIGINT))
		printf ("There is SIGINT.\n");
	else
		printf ("There isn't SIGINT.\n");

	if (sigismember (&set, SIGQUIT))
		printf ("There is SIGQUIT.\n");
	else
		printf ("There isn't SIGQUIT.\n");

	return 0;
}
