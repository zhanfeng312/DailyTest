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
    ����һ: ����socket
    */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket error");
        exit(1);
    }

    //��serveraddr������ip, port �� ��ַ������
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    //��ip��ַת���������ֽ��������serveraddr��
    inet_pton(AF_INET, argv[1],
                &serveraddr.sin_addr.s_addr);
    /*
    �����: �ͻ��˵���connect �������ӵ���������
    */
    if (connect(sockfd,
                (struct sockaddr*)&serveraddr,
                sizeof (serveraddr)) < 0){
        perror("connect error");
        exit(1);
    }

    /*
    ������: ����IO����(read/write)�ͷ������˽���˫��ͨ��
    */

    char buff[512] = {0};
    size_t size;
    char *prompt = ">";

    while (1) {

        memset(buff, 0, sizeof(buff));
        write(STDOUT_FILENO, prompt, 1);
        size = read(STDIN_FILENO, buff, sizeof(buff));
        if (size < 0) continue;
        buff[size - 1] = '\0';

        if (write(sockfd, buff, sizeof(buff)) < 0) {
            perror("write error");
            continue;
        }
        else {
            if (read(sockfd, buff, sizeof(buff) < 0)) {
                perror("read error");
                continue;
            }
            else {
                printf("%s\n", buff);
            }
        }
    }

    /*
    ������: �ر�socket
    */
    close(sockfd);
    
    return 0;
}
