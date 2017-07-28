#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	int status;

	if ((status = system (NULL)) == -1) {
		perror ("system");
		return -1;
	}

	if (! status) {
		printf ("shell不可用！\n");
		return -1;
	}

	if ((status = system ("ls -l")) == -1) {
		perror ("system");
		return -1;
	}

	printf ("ls进程以%#x状态退出。\n", WEXITSTATUS (status));

	if ((status = system ("ps -ef")) == -1) {
		perror ("system");
		return -1;
	}

	printf ("ps进程以%#x状态退出。\n", WEXITSTATUS (status));

	return 0;
}
