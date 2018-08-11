#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>

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

void do_service(int fd)
{
    /*和客户端进行读写操作（双向通信）*/
    char buff[512];
    while (1) {
        memset(buff, 0, sizeof(buff));
        size_t size;
        if ((size = read(fd, buff, sizeof(buff))) < 0) {
            perror("protocol error");
            break;
        }
        else if (size == 0) {
            break;
        }
        else {
            printf("%s\n", buff);
            if (write(fd, buff, sizeof(buff)) < 0) {
                if (errno == EPIPE) {
                    break;
                }
                perror("protocol error");
            }
        }
    }
}

void out_fd(int fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if (getpeername(fd, (struct sockaddr*)&addr, &len) < 0) {
        perror("getpeername error");
        return;
    }

    char ip[16];
    memset(ip, 0, sizeof(ip));
    int port = ntohs(addr.sin_port);
    inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));
    printf("%16s(%5d) closed!\n", ip, port);
}

void* th_fn(void *arg)
{
    int fd = *((int*)arg);

    do_service(fd);
    out_fd(fd);
    close(fd);
    return (void*)0;
}

int main(int argc, char *argv[])
{
    if (argc < 2){
        
        printf("usage: %s port\n", argv[0]);
        exit(1);
    }

    if(signal(SIGINT, sig_handler) == SIG_ERR){
        
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
    2、调用bind函数将socket 和地址(包括ip, port)进行绑定
    */

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    //往地址中填入ip, port, internet地址族类型
    serveraddr.sin_family = AF_INET; //IPV4
    serveraddr.sin_port = htons(atoi(argv[1]));//port
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
                      
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

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while (1) {
        //主线程负责调用accept去获得客户端的连接
        int fd = accept(sockfd, NULL, NULL);
        if (fd < 0) {

            perror("accept error");
            continue;
        }

        /*
        5、启动子线程去调用IO函数(read/write) 和
        连接的客户端进行双向的通信

        两种方式 默认状态、分离状态
        pthread_join 阻塞，等待子线程结束，释放线程资源

        服务器 一般不会退出
        并发处理
        */

        pthread_t threadId;
        int err;
        //以分离状态启动子线程
        if ((err = pthread_create(&threadId, &attr, th_fn, (void*)&fd)) != 0) {

            perror("pthread_create error");
        }
        pthread_attr_destroy(&attr); //主线程去除attr属性
    }

    return 0;
}