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

        /*6���ر�socket*/
        close(sockfd);
        exit(1);
    }
}

/*��������ӵĿͻ�����Ϣ*/
void out_addr(struct sockaddr_in *clientaddr)
{
    //���˿ڴ������ֽ���ת���������ֽ���
    int port = ntohs(clientaddr->sin_port);
    char ip[16] = {0};

    //��ip��ַ�������ֽ���ת���ɵ��ʮ����
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

    //���������˻�õ�ϵͳʱ��д�ص��ͻ���
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
    1������socket
      socket�������ں��У���һ���ṹ��
      AF_INET: IPV4
      SOCK_STREAM : tcp
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket error");
        exit(1);
    }

    /*
    2������bind������socket �͵�ַ(����ip,port)���а�
    */

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    //����ַ������ip, port, internet��ַ������
    serveraddr.sin_family = AF_INET; //IPV4
    serveraddr.sin_port = htons(atoi(argv[1]));//port
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&serveraddr,
                      sizeof(serveraddr)) < 0){
                      
        perror("bind error");
        exit(1);
    }

    /*
    3������listen ������������(ָ��port����)
       ֪ͨϵͳȥ�������Կͻ��˵���������
       (�����յ��Ŀͻ�������������õ���Ӧ�Ķ�����)

       �ڶ�������: ָ�����еĳ���
    */

    if (listen(sockfd, 10) < 0){
        
        perror("listen error");
        exit(1);
    }


    /*
    4������accept �����Ӷ����л��
       һ���ͻ��˵��������ӣ��������µ�socket������

       ע��: ��û�пͻ������ӣ����ô˺�����������ֱ��
       ���һ���ͻ��˵�����
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
        5������IO����(read/write) ��
        ���ӵĿͻ��˽���˫���ͨ��
        */
        out_addr(&clientaddr);
        do_service(fd);

        /*6���ر�socket*/
        close(fd);
    }

    return 0;
}