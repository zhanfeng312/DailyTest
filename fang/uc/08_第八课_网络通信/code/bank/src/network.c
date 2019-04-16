#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../inc/network.h"

int init (unsigned short type) {
	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (type);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
		perror ("bind");
		close (sockfd);
		return -1;
	}

	if (listen (sockfd, 1024) == -1) {
		perror ("listen");
		close (sockfd);
		return -1;
	}

	return sockfd;
}

void deinit (int sockfd) {
	close (sockfd);
}

int rcvreq (int sockfd, void* req, size_t len) {
	int connfd = -1;

	for (;;) {
		struct sockaddr_in addrcli = {};
		socklen_t addrlen = sizeof (addrcli);
		if ((connfd = accept (sockfd, (struct sockaddr*)&addrcli,
			&addrlen)) == -1) {
			perror ("accept");
			continue;
		}

		printf ("客户交易：%s\n", inet_ntoa (addrcli.sin_addr));

		pid_t pid = fork ();
		if (pid == -1) {
			perror ("fork");
			close (connfd);
			continue;
		}

		if (pid == 0)
			break;

		close (connfd);
	}

	ssize_t rb = recv (connfd, req, len, 0);
	if (rb == -1) {
		perror ("recv");
		close (connfd);
		return -1;
	}

	if (rb == 0) {
		printf ("Client shutdown !\n");
		close (connfd);
		return -1;
	}

	return connfd;
}

int sndres (int connfd, const void* res, size_t len) {
	if (send (connfd, res, len, 0) == -1) {
		perror ("send");
		close (connfd);
		return -1;
	}

	close (connfd);
	return 0;
}

int sndreq (const char* server, unsigned short type, const void* req,
	size_t len) {
	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (type);
	addr.sin_addr.s_addr = inet_addr (server);

	if (connect (sockfd, (struct sockaddr*)&addr,
		sizeof (addr)) == -1) {
		perror ("connect");
		close (sockfd);
		return -1;
	}

	if (send (sockfd, req, len, 0) == -1) {
		perror ("send");
		close (sockfd);
		return -1;
	}

	return sockfd;
}

int rcvres (int sockfd, void* res, size_t len) {
	ssize_t rb = recv (sockfd, res, len, 0);
	if (rb == -1) {
		perror ("recv");
		close (sockfd);
		return -1;
	}

	if (rb == 0) {
		printf ("Server shutdown !\n");
		close (sockfd);
		return -1;
	}

	close (sockfd);
	return 0;
}
