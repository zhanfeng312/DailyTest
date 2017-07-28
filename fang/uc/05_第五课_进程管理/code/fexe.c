#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	pid_t pid = vfork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		if (execlp ("ls", "ls", "-l", NULL) == -1) {
			perror ("execl");
			return -1;
		}
		return 0;
	}

	int status;

	if (waitpid (pid, &status, 0) == -1) {
		perror ("waitpid");
		return -1;
	}

	printf ("ls进程以%#x状态退出。\n", WEXITSTATUS (status));

	if ((pid = fork ()) == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		char* argv[] = {"ps", "-ef", NULL};
		if (execvp ("ps", argv) == -1) {
			perror ("execv");
			return -1;
		}
		return 0;
	}

	if (waitpid (pid, &status, 0) == -1) {
		perror ("waitpid");
		return -1;
	}

	printf ("ps进程以%#x状态退出。\n", WEXITSTATUS (status));

	return 0;
}
