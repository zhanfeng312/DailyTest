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
	printf ("转账服务：即将停止。\n");
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

			printf ("转账服务：全部子进程都已退出。\n");
			break;
		}

		if (pid)
			printf ("转账服务：发现%u子进程退出。\n", pid);
		else {
			printf ("转账服务：暂时没有子进程退出。\n");
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

	if ((g_sockfd = init (TYPE_TRANSFER)) == -1)
		return -1;

	printf ("转账服务：启动就绪。\n");

	TRANSFER_REQUEST req;

	int connfd = rcvreq (g_sockfd, &req, sizeof (req));
	if (connfd == -1)
		return -1;

	TRANSFER_RESPOND res = {""};
	ACCOUNT acc[2];

	if (get (req.id[0], &acc[0]) == -1) {
		sprintf (res.error, "无效账号！");
		goto send_respond;
	}

	if (strcmp (req.name[0], acc[0].name)) {
		sprintf (res.error, "无效户名！");
		goto send_respond;
	}

	if (strcmp (req.passwd, acc[0].passwd)) {
		sprintf (res.error, "密码错误！");
		goto send_respond;
	}

	if (req.money > acc[0].balance) {
		sprintf (res.error, "余额不足！");
		goto send_respond;
	}

	if (get (req.id[1], &acc[1]) == -1) {
		sprintf (res.error, "无效对方账号！");
		goto send_respond;
	}

	if (strcmp (req.name[1], acc[1].name)) {
		sprintf (res.error, "无效对方户名！");
		goto send_respond;
	}

	acc[0].balance -= req.money;

	if (update (&acc[0]) == -1) {
		sprintf (res.error, "更新账户失败！");
		goto send_respond;
	}

	acc[1].balance += req.money;

	if (update (&acc[1]) == -1) {
		sprintf (res.error, "更新对方账户失败！");
		goto send_respond;
	}

	res.balance = acc[0].balance;

send_respond:

	if (sndres (connfd, &res, sizeof (res)) == -1)
		return -1;

	return 0;
}
