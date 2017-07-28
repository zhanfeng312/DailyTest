#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		int status = 0x12345678;

		printf ("子进程：我是%u进程。我要以%#x状态退出。\n",
			getpid (), status);

		return status;
	}

	printf ("父进程：我要等待子进程...\n");

	int status;
	pid = wait (&status);

	printf ("父进程：发现%u进程以%#x状态退出了。\n", pid,
		WEXITSTATUS (status));

	return 0;
}
