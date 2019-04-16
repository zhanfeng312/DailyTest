#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>
#include "../inc/bank.h"
#include "../inc/network.h"
#include "../inc/dao.h"

static int g_sockfd = -1;

void sigint (int signum) {
	printf ("开户服务：即将停止。\n");
	deinit (g_sockfd);
	exit (0);
}

void sigchld (int signum) {
	for (;;) {
		pid_t pid = waitpid (-1, 0, WNOHANG);
		if (pid == -1) {
			if (errno != ECHILD) {
				perror ("waitpid");
				exit (-1);
			}

			printf ("开户服务：全部子进程都已退出。\n");
			break;
		}

		if (pid)
			printf ("开户服务：发现%u子进程退出。\n", pid);
		else {
			printf ("开户服务：暂时没有子进程退出。\n");
			break;
		}
	}
}

int main (void) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	if (signal (SIGCHLD, sigchld) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	if ((g_sockfd = init (TYPE_OPEN)) == -1)
		return -1;

	printf ("开户服务：启动就绪。\n");

	OPEN_REQUEST req;

	int connfd = rcvreq (g_sockfd, &req, sizeof (req));
	if (connfd == -1)
		return -1;

	OPEN_RESPOND res = {""};
	ACCOUNT acc;

	if ((acc.id = genid ()) == -1) {
		sprintf (res.error, "创立账户失败！");
		goto send_respond;
	}

	strcpy (acc.name, req.name);
	strcpy (acc.passwd, req.passwd);
	acc.balance = req.balance;

	if (save (&acc) == -1) {
		sprintf (res.error, "保存账户失败！");
		goto send_respond;
	}

	res.id = acc.id;

send_respond:

	if (sndres (connfd, &res, sizeof (res)) == -1)
		return -1;

	return 0;
}
