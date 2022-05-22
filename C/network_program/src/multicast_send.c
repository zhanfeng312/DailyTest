#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MULTICAST_IP "239.0.0.10"
#define DEST_MULTICAST_PORT 8888
#define LOCAL_MULTICAST_PORT 7777

int main(int argc, char *argv[])
{
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockFd < 0) {
        perror("socket error");
        exit(-1);
    }

    /* 初始化并绑定套接字，该操作可选，不一定非要绑定本地端口 */
    struct sockaddr_in localAddr;
    (void)memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(LOCAL_MULTICAST_PORT);
    localAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockFd, (const struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
        perror("bind error");
        exit(-1);
    }

    /* 第一种格式: */
    struct in_addr addr;
    (void)inet_pton(AF_INET, "192.168.119.129", &addr.s_addr);
    //指定多播输出接口的IP地址
    (void)setsockopt(sockFd, IPPROTO_IP, IP_MULTICAST_IF, &addr, sizeof(addr));

    const char *str = "hello world";
    struct sockaddr_in destAddr;
    (void)memset(&destAddr, 0, sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(DEST_MULTICAST_PORT);
    inet_pton(AF_INET, MULTICAST_IP, &destAddr.sin_addr.s_addr);
    while (1) {
        ssize_t size = sendto(sockFd, str, strlen(str), 0, (const struct sockaddr *)&destAddr,
                              sizeof(destAddr));
        if (size == -1) {
            perror("sendto error");
            break;
        }
        printf("组播的数据: %s\n", str);
        (void)sleep(1);
    }
    (void)close(sockFd);
    return 0;
}