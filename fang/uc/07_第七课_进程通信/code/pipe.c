#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	printf ("父进程：创建管道...\n");

	int pipefd[2];
	if (pipe (pipefd) == -1) {
		perror ("pipe");
		return -1;
	}

	printf ("父进程：创建进程...\n");

	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}

	if (pid == 0) {
		printf ("子进程：关闭写端...\n");

		close (pipefd[1]);

		printf ("子进程：接收数据...\n");

		for (;;) {
			char buf[1024];

			ssize_t rb = read (pipefd[0], buf, sizeof (buf));
			if (rb == -1) {
				perror ("read");
				return -1;
			}

			if (! rb)
				break;

			puts (buf);
		}

		printf ("子进程：关闭读端...\n");

		close (pipefd[0]);

		printf ("子进程：大功告成！\n");

		return 0;
	}

	printf ("父进程：关闭读端...\n");

	close (pipefd[0]);

	printf ("父进程：发送数据...\n");

	for (;;) {
		char buf[1024];
		gets (buf);

		if (! strcmp (buf, "!"))
			break;

		if (write (pipefd[1], buf, (strlen (buf) + 1) *
			sizeof (buf[0])) == -1) {
			perror ("write");
			return -1;
		}
	}

	printf ("父进程：关闭写端...\n");

	close (pipefd[1]);

	if (wait (0) == -1) {
		perror ("wait");
		return -1;
	}

	printf ("父进程：大功告成！\n");

	return 0;
}
