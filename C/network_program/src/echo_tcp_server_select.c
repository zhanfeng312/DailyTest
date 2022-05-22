#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include "vector_fd.h"

VectorFD *vfd;
int sockfd = 0;

void sig_handler(int signo)
{
    if (signo == SIGINT){

        printf("server close\n");
        /*6、关闭socket*/
        close(sockfd);
        //销毁动态数组
        destory_vector_fd(vfd);
        exit(1);
    }
}

/*
  fd 对应于某个连接的客户端
  和某一个连接的客户端进行双向通信（非阻塞方式）
*/
void do_service(int fd)
{
    char buff[512];
    memset(buff, 0, sizeof(buff));
    /*因为采用非阻塞方式，若读不到数据直接返回
      直接服务于下一个客户端
      因此不需要判断size 小于0的情况
    */
    size_t size = read(fd, buff, sizeof(buff));
    if (size == 0) {
        char info[] = "client closed\n";
        //write不带缓存
        write(STDOUT_FILENO, info, sizeof(info));
        //从动态数组中删除对应的fd
        remove_fd(vfd, fd);
        //关闭对应客户端的socket
        close(fd);
    }else if (size > 0) {
        printf("%s\n", buff);
        if (write(fd, buff, size) < 0) {
            if (errno == EPIPE) {//客户端关闭连接
                perror("write error");
                remove_fd(vfd, fd);
                close(fd);
            }
        }
    }
}

/*
    遍历动态数组中所有的描述符并加入到描述符集set中
    同时此函数返回动态数组中最大的那个描述符
*/
int add_set(fd_set *set)
{
    FD_ZERO(set); //清空描述符集
    int max_fd = vfd->fd[0];
    int i = 0;
    for (; i < vfd->counter; i++) {
        int fd = get_fd(vfd, i);
        if (fd > max_fd)
            max_fd = fd;
        FD_SET(fd, set);
    }
    return max_fd;
}

void* th_fn(void *arg)
{
    struct timeval t;
    t.tv_sec = 2;
    t.tv_usec = 0;
    int n = 0;
    int maxfd;
    fd_set set;

    maxfd = add_set(&set);

    /*
    调用select函数会阻塞，委托内核去检查转入的描述符集
    是否准备好，若有则返回准备好的描述符数
    超时则返回0

    第一个参数为描述符集中描述符的范围（最大描述符+1）
    */
    while ((n = select(maxfd + 1,&set,
                       NULL, NULL, &t)) >= 0) {
        if (n > 0) {
            int i = 0;
            for (; i < vfd->counter; i++) {
                int fd = get_fd(vfd, i);
                if (FD_ISSET(fd, &set))
                    do_service(fd);
            }
        }

        //重新设置时间和清空描述符集
        t.tv_sec = 2;
        t.tv_usec = 0;
        //重新遍历动态数组中最新的描述符放置到描述符集中
        maxfd = add_set(&set);
    }

    return (void*)0;
}

void out_addr(struct sockaddr_in *clientaddr)
{
    char ip[16];
    memset(ip, 0, sizeof(ip));
    int port = ntohs(clientaddr->sin_port);
    inet_ntop(AF_INET, &clientaddr->sin_addr.s_addr, ip, sizeof(ip));
    printf("%s(%d) connected!\n", ip, port);
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

    //创建放置套接字描述符fd的动态数组
    vfd = cerate_vector_fd();

    //以分离状态创建子线程
    pthread_t thid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int err;
    if ((err = pthread_create(&thid, &attr, th_fn, (void*)0)) != 0) {
        perror("pthread_create error");
        exit(1);
    }
    //主线程去除attr属性
    pthread_attr_destroy(&attr);

    /*
     1) 主控线程获得客户端的连接，将新的socket描述符
        放置到动态数组中
     2）a) 启动的子线程调用select函数委托内核去检查
           传入到select中的描述符是否准备好
        b）利用FD_ISSET来找出准备好的那些描述符
           并和对应的客户端进行双向通信（非阻塞）
    */

    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    while (1) {
        int fd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
        if (fd < 0) {
            perror("accept error");
            continue;
        }
        out_addr(&clientaddr);

        //将返回新的socket描述符加入到动态数组中
        add_fd(vfd, fd);
    }

    return 0;
}