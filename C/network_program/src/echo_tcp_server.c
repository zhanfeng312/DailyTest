#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(-1);
    }

    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(lfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(lfd, 128); //设置客户端同时连接的上限数

    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    char ip[16] = {0};
    int cfd = accept(lfd, (struct sockaddr *)&clientAddr, &len);
    printf("client IP:%s, port: %d connected.\n",
           inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, ip, sizeof(ip)),
           ntohs(clientAddr.sin_port));

    char buf[1024] = {0};
    while (1) {
        int n = read(cfd, buf, sizeof(buf));
        if (n == 0) {
            printf("client close\n");
            close(cfd);
            break;
        }
        printf("%s", buf);
        write(cfd, buf, n);
    }

    close(lfd);

    return 0;
}