#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>


int main(int argc, char *argv[])
{
    if (argc < 3){

        printf("usage: %s ip port\n", argv[0]);
        exit(1);
    }

    /*
    步骤一: 创建socket
    */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){

        perror("socket error");
        exit(1);
    }

    //往serveraddr中填入ip, port 和 地址族类型
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    //将ip地址转换成网络字节序后填入serveraddr中
    inet_pton(AF_INET, argv[1], &serveraddr.sin_addr.s_addr);
    /*
    步骤二: 客户端调用connect 函数连接到服务器端
    */
    if (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof (serveraddr)) < 0){

        perror("connect error");
        exit(1);
    }

    /*
    步骤三: 调用IO函数(read/write) 和 服务器端进行通信
    */

    char buffer[1024] = {0};
    size_t size;

    if ((size = read(sockfd, buffer, sizeof(buffer))) < 0){

        perror("read error");
        exit(1);
    }
    
    if (write(STDOUT_FILENO, buffer, size) != size){

        perror("write error");
        exit(1);
    }

    /*
    步骤四: 关闭socket
    */
    close(sockfd);
    
    
    return 0;
}
