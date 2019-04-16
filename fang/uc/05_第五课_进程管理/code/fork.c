#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf ("%u进程：我要调用fork()了...\n", getpid ());

	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		printf ("%u进程：我是%u进程的子进程。\n", getpid (),
			getppid ());
		return 0;
	}

	printf ("%u进程：我是%u进程的父进程。\n", getpid (), pid);
	sleep (1);

	return 0;
}
