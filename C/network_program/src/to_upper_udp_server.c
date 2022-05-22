#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

static int g_socketFd = -1;

static void OutAddr(const struct sockaddr_in *clientAddr)
{
    char ip[16] = {0};
    if (inet_ntop(AF_INET, &clientAddr->sin_addr.s_addr, ip, sizeof(ip)) == NULL) {
        perror("inet_ntop error");
        exit(1);
    }
    printf("Client: %s(%d)\n", ip, ntohs(clientAddr->sin_port));
}

//不传入其他参数时, argc为1, argv[0]表示程序名
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    g_socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (g_socketFd == -1) {
        perror("socket error");
        exit(1);
    }
    printf("g_socketFd is %d\n", g_socketFd);

    int opt = 1;
    //设置套接字选项
    if (setsockopt(g_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt error");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    (void)memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = atoi(argv[1]);
    //serverAddr 和 len都为传入参数
    if (bind(g_socketFd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind error");
        exit(1);
    }

    while (1) {
        char buf[1024] = {0};
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(clientAddr);

        //clientAddr为传出参数，代表接收到的客户端信息
        //len为传入传出参数, 当为传入参数时代表clientAddr长度, 当为传出参数时, 代表得到的客户端长度
        ssize_t size = recvfrom(g_socketFd, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, &len);
        if (size == -1) {
            perror("recvfrom error");
            exit(1);
        }

        OutAddr(&clientAddr);
        //write(STDOUT_FILENO, buf, size);

        int i = 0;
        for (; i < size; i++) {
            buf[i] = toupper(buf[i]);
        }

        if (sendto(g_socketFd, buf, size, 0, (const struct sockaddr *)&clientAddr, len) < 0) {
            perror("sendto error");
            exit(1);
        }
    }

    return 0;
}