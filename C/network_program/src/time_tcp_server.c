#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <signal.h>
#include <time.h>

static int g_serverFd = 0;

void sig_handler(int signo)
{
    if (signo == SIGINT) {
        printf("server close!\n");
        /*6、关闭socket*/
        close(g_serverFd);
        exit(1);
    }
}

/*输出已连接的客户端信息*/
void out_addr(const struct sockaddr_in *clientAddr)
{
    //将端口从网络字节序转换成主机字节序
    uint16_t port = ntohs(clientAddr->sin_port);
    char ip[16] = {0};

    //将ip地址从网络字节序转换成点分十进制
    inet_ntop(AF_INET, &clientAddr->sin_addr.s_addr, ip, sizeof(ip));

    printf("client: %s(%u) connected\n", ip, port);
}

void do_service(int fd)
{
    time_t t = time(0);
    char *s = ctime(&t);
    size_t size = strlen(s) * sizeof(char);

    //将服务器端获得的系统时间写回到客户端
    if (write(fd, s, size) != size) {
        perror("write error!");
    }
}

int main(int argc, char *argv[])
{
    //判断输入参数个数
    if (argc < 2) {
        fprintf(stderr, "usage: %s port\n", argv[0]);
        exit(1);
    }

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("signal sig_handler error");
        exit(1);
    }

    /*
    1、创建socket
      socket创建在内核中
      AF_INET: IPv4
      AF_INET6 IPv6

      SOCK_STREAM:tcp
      SOCK_DGRAM: udp
    */
    g_serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (g_serverFd < 0) {
        perror("socket error");
        exit(1);
    }

    /*
    2、调用bind函数将socket和地址(包括ip,port)进行绑定
    */
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    //往地址中填入ip, port, internet地址族类型
    serverAddr.sin_family = AF_INET; //IPV4
    serverAddr.sin_port = htons(atoi(argv[1]));//port
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(g_serverFd, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    /*
    3、调用listen 函数启动监听
       通知系统去接收来自客户端的连接请求
       (将接收到的客户端连接请求放置到对应的队列中)
       第二个参数: 指定队列的长度
    */
    if (listen(g_serverFd, 10) < 0) {
        perror("listen error");
        exit(1);
    }

    /*
    4、调用accept 函数从队列中获得
       一个客户端的请求连接，并返回新的socket描述符
       注意: 若没有客户端连接，调用此函数会阻塞，直到
       获得一个客户端的链接
    */
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    while (1) {
        //连接上来的客户端信息保存在clientaddr中
        int clientFd = accept(g_serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientFd < 0) {
            perror("accept error");
            continue;
        }

        /*
        5、调用IO函数(read/write) 和 连接的客户端进行通信
        */
        out_addr(&clientAddr);
        do_service(clientFd);

        /*6、关闭socket*/
        close(clientFd);
    }
    return 0;
}