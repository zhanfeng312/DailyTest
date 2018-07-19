#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
char buf[1024];
char buf1[1024];
void* func(void* arg);
int main (int argc, char* argv[]) {
    if (argc < 2){
        fprintf(stderr, "用法: %s <端口号>\n", argv[0]);
        return -1;
    }
    memset(buf, 0, 1024);
    memset(buf1, 0, 1024);
    printf("服务器: 创建网络数据流套结字...\n");
    int sockfd = socket (AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror ("socket");
        return -1;
    }
    printf("服务器: 准备通信地址并绑定...\n");
    struct sockaddr_in addr;  //网络地址类型
    addr.sin_family = AF_INET;
    addr.sin_port = htons (atoi (argv[1])); //主机字节序->网络字节序
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind (sockfd, (struct sockaddr*)&addr,
                sizeof (addr)) == -1) {
        perror ("bind");
        return -1;
    }
    printf("服务器: 监听套结字...\n");
    if (listen (sockfd, 1024) == -1) {
        perror ("listen");
        return -1;
    }
    for(;;){
        printf("服务器：等待链接请求...\n");
        struct sockaddr_in addrcli = {};
        socklen_t addrlen = sizeof (addrcli);
        int connfd = accept (sockfd, (struct sockaddr*)&addrcli, &addrlen);
        if (connfd == -1) {
            perror ("accept");
            return -1;
        }
        printf("服务器:收到%s:%u客户机的连接信息\n",
                inet_ntoa(addrcli.sin_addr),ntohs(addrcli.sin_port));
        printf("服务器:创建子进程去和客户端交流,主进程等待其它链接请求.\n");
        pid_t pidd = fork();
        if (pidd == -1){
            perror("fork");
            return -1;
        }
        if (pidd == 0){
            printf("创建线程去给客户端发送数据\n");
            pthread_t pid;
            pthread_create(&pid, NULL, func, &connfd);
            while(1){
                ssize_t rd = recv(connfd, buf1, sizeof(buf1), 0);
                if (rd == 0){
                    printf("客户机已关闭连接.\n");
                    break;
                }
                printf("%s\n", buf1);
            }
            printf("关闭与客户端的连接.\n");
            close (sockfd);
            return 0;
        }
    }
    return 0;
}
void* func(void* arg){
    int connfd = *((int*) arg);
    for(;;){
        scanf("%s", buf);
        send(connfd, buf, sizeof(buf), 0);
    }
    return arg;
}
