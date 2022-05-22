#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s ip port\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket error");
        exit(1);
    }

    int opt = 1;
    //采用广播方式发送
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    struct sockaddr_in recvAddr;
    memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &recvAddr.sin_addr.s_addr);

    printf("I will broadcast...\n");
    while (1) {
        char *info = "hello world\n";
        size_t size = strlen(info) * sizeof(char);

        if (sendto(sockfd, info, size, 0, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) < 0) {
            perror("sendto error");
            exit(1);
        } else {
            printf("broadcast success\n");
        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}