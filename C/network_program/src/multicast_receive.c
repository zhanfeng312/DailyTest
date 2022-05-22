#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

#define LOCAL_MULTICAST_PORT 8888
#define MULTICAST_IP "239.0.0.10"

int main(int argc, char *argv[])
{
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockFd < 0) {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in localAddr;
    (void)memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(LOCAL_MULTICAST_PORT);
    if (bind(sockFd, (const struct sockaddr *)&localAddr, sizeof(localAddr)) == -1) {
        perror("bind error");
        exit(-1);
    }

    struct ip_mreq op;
    //指定加入组播的本地接口IP地址
    (void)inet_pton(AF_INET, "192.168.119.129", &op.imr_interface.s_addr);
    //指定加入组播的组播组IP地址
    (void)inet_pton(AF_INET, MULTICAST_IP, &op.imr_multiaddr.s_addr);
    //加入组播
    (void)setsockopt(sockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &op, sizeof(op));

    char buf[128] = {0};
    while (1) {
        memset(buf, 0, sizeof(buf));
        ssize_t size = recvfrom(sockFd, buf, sizeof(buf), 0, NULL, 0);
        if (size == -1) {
            perror("recvfrom failed.");
            break;
        }
        printf("%s\n", buf);
    }
    (void)close(sockFd);
    return 0;
}