#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>

int main (void) {
	printf ("获取消息队列...\n");

	key_t key = ftok (".", 100);
	if (key == -1) {
		perror ("ftok");
		return -1;
	}

	int msqid = msgget (key, 0);
	if (msqid == -1) {
		perror ("msgget");
		return -1;
	}

	printf ("从消息队列(0x%08x/%d)接收消息...\n", key, msqid);

	for (;;) {
		struct {
			long mtype;
			char mtext[1024];
		}	msgbuf = {};

		ssize_t msgsz = msgrcv (msqid, &msgbuf,
			sizeof (msgbuf.mtext) - sizeof (msgbuf.mtext[0]), 1234,
			MSG_NOERROR/* | IPC_NOWAIT*/);
		if (msgsz == -1)
			if (errno == EIDRM) {
				printf ("消息队列(0x%08x/%d)已销毁！\n", key, msqid);
				break;
			}
			else
			if (errno == ENOMSG) {
				printf ("现在没有消息，干点儿别的...\n");
				sleep (1);
			}
			else {
				perror ("msgrcv");
				return -1;
			}
		else
			printf ("%04d< %s\n", msgsz, msgbuf.mtext);
	}

	printf ("大功告成！\n");

	return 0;
}
