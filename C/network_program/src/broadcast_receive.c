#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

//不传入其他参数时, argc为1, argv[0]表示程序名
int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(1);
    }

    int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd == -1) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in recvAddr;
    (void)memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &recvAddr.sin_addr.s_addr);
    recvAddr.sin_port = htons(atoi(argv[2]));

    if (bind(socketFd, (const struct sockaddr *)&recvAddr, sizeof(recvAddr)) == -1) {
        perror("bind error");
        exit(1);
    }

    while (1) {
        char buf[1024] = {0};
        ssize_t size = recvfrom(socketFd, buf, sizeof(buf), 0, NULL, NULL);
        if (size == -1) {
            perror("recvfrom error");
            exit(1);
        }
        write(STDOUT_FILENO, buf, size);
    }
    return 0;
}