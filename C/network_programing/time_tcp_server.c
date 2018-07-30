#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <signal.h>
#include <time.h>

int sockfd = 0;

void sig_handler(int signo)
{
    if (signo == SIGINT){
        
        printf("server close\n");

        /*6、关闭socket*/
        close(sockfd);
        exit(1);
    }
}

/*输出已连接的客户端信息*/
void out_addr(struct sockaddr_in *clientaddr)
{
    //将端口从网络字节序转换成主机字节序
    int port = ntohs(clientaddr->sin_port);
    char ip[16] = {0};

    //将ip地址从网络字节序转换成点分十进制
    inet_ntop(AF_INET,
              &clientaddr->sin_addr.s_addr, ip, sizeof(ip));
    printf("client: %s(%d) connected\n", ip, port);
}

void do_service(int fd)
{
    long t = time(0);
// TODO: ctime
    char *s = ctime(&t);
    size_t size = strlen(s) * sizeof(char);

    //将服务器端获得的系统时间写回到客户端
// TODO: write
    if (write(fd, s, size) != size){
        perror("write error!");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2){
        
        printf("usage: %s port\n", argv[0]);
        exit(1);
    }

    if(signal (SIGINT, sig_handler) == SIG_ERR){
        
        perror("signal sig_handler error");
        exit(1);
    }

    /*
    1、创建socket
      socket创建在内核中，是一个结构体
      AF_INET: IPV4
      SOCK_STREAM : tcp
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket error");
        exit(1);
    }

    /*
    2、调用bind函数将socket 和地址(包括ip,port)进行绑定
    */

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    //往地址中填入ip, port, internet地址族类型
    serveraddr.sin_family = AF_INET; //IPV4
    serveraddr.sin_port = htons(atoi(argv[1]));//port
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&serveraddr,
                      sizeof(serveraddr)) < 0){
                      
        perror("bind error");
        exit(1);
    }

    /*
    3、调用listen 函数启动监听(指定port监听)
       通知系统去接收来自客户端的连接请求
       (将接收到的客户端连接请求放置到对应的队列中)

       第二个参数: 指定队列的长度
    */

    if (listen(sockfd, 10) < 0){
        
        perror("listen error");
        exit(1);
    }


    /*
    4、调用accept 函数从队列中获得
       一个客户端的请求连接，并返回新的socket描述符

       注意: 若没有客户端连接，调用此函数会阻塞，直到
       获得一个客户端的链接
    */

    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    while (1) {
        int fd = accept(sockfd,
            (struct sockaddr*)&clientaddr,
            &clientaddr_len);
        if (fd < 0) {

            perror("accept error");
            continue;
        }

        /*
        5、调用IO函数(read/write) 和
        连接的客户端进行双向的通信
        */
        out_addr(&clientaddr);
        do_service(fd);

        /*6、关闭socket*/
        close(fd);
    }

    return 0;
}