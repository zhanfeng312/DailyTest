#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
char buf[1024];
char buf1[1024];
void* func(void* arg);
void doexit(int sock, void* arg){
    int sockfd = *(int*)arg;
    printf("关闭与服务器的连接...\n");
    close(sockfd);
    printf("客户机：大功告成!\n");
}   
int main (int argc, char* argv[]){
    if (argc < 3) {
        fprintf(stderr, "用法： %s<服务器IP地址><端口号>\n", argv[0]);
        return -1;
    }
    memset(buf, 0, 1024);
    memset(buf1, 0, 1024);
    printf("客户机:创建网络数据流套结字...\n");
    int sockfd = socket (AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }
    printf("客户机： 准备地址并连接...\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons (atoi (argv[2]));
    addr.sin_addr.s_addr = inet_addr (argv[1]);
    if (connect (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
        perror ("connent");
        return -1;
    }
    if (on_exit(doexit, &sockfd) == -1){
        perror("atexit");
        return -1;
    }
    printf("创建线程去给服务器发送数据...\n");
    printf("主线程接受来自服务器的数据...\n");
    pthread_t thread;
    pthread_create(&thread, NULL, func, &sockfd);
    /*int errno = 1;
    errno = pthread_join(thread, NULL);
    if(errno == 0){
        printf("关闭套结字...\n");
        close(sockfd);
        goto usage;
    }*/
    while(1){
        ssize_t rb = recv (sockfd, buf1, sizeof (buf1), 0);
        if (rb == 0){
            break;
        }
        printf("%s\n", buf1);
    }
    return 0;
}
void* func(void* arg){
    int sockfd = *((int*)arg);
    for(;;){
        scanf("%s", buf);
        if (! strcmp(buf, "!"))
            break;
        else{
            if (send(sockfd, buf, sizeof(buf), 0) == -1){
                perror("send");
                return arg;
            }
        }
    }
    exit(1);
    return arg;
}


