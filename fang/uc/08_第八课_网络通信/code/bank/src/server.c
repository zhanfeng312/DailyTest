#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include "../inc/bank.h"

typedef struct tag_Service {
	char  srv_path[PATH_MAX+1];
	pid_t srv_pid;
}	SERVICE;

static SERVICE g_srv[] = {
	{"./open",     -1},
	{"./close",    -1},
	{"./save",     -1},
	{"./withdraw", -1},
	{"./query",    -1},
	{"./transfer", -1}
};

int start (void) {
	printf ("启动业务服务...\n");

	size_t i;
	for (i = 0; i < sizeof (g_srv) / sizeof (g_srv[0]); i++) {
		if ((g_srv[i].srv_pid = vfork ()) == -1) {
			perror ("vfork");
			return -1;
		}

		if (g_srv[i].srv_pid == 0) {
			if (execl (g_srv[i].srv_path, g_srv[i].srv_path,
				NULL) == -1) {
				perror ("execl");
				return -1;
			}

			return 0;
		}
	}

	return 0;
}

int stop (void) {
	printf ("停止业务服务...\n");

	size_t i;
	for (i = 0; i < sizeof (g_srv) / sizeof (g_srv[0]); i++)
		if (kill (g_srv[i].srv_pid, SIGINT) == -1) {
			perror ("kill");
			return -1;
		}

	for (;;)
		if (wait (0) == -1) {
			if (errno != ECHILD) {
				perror ("wait");
				return -1;
			}

			break;
		}

	return 0;
}

int main (void) {
	if (start () == -1)
		return -1;

	sleep (1);
	printf ("按<回车>退出...\n");
	getchar ();

	if (stop () == -1)
		return -1;

	return 0;
}
