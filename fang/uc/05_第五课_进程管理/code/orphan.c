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
		sleep (1);
		printf ("\n%u进程：我是被%u进程收养的孤儿进程。", getpid (),
			getppid ());

		return 0;
	}

	printf ("%u进程：我是%u进程的父进程。\n", getpid (), pid);

	return 0;
}
