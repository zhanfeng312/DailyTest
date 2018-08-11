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
        /*6���ر�socket*/
        close(sockfd);
        exit(1);
    }
}

void do_service(int fd)
{
    /*�Ϳͻ��˽��ж�д������˫��ͨ�ţ�*/
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
    2������bind������socket �͵�ַ(����ip, port)���а�
    */

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    //����ַ������ip, port, internet��ַ������
    serveraddr.sin_family = AF_INET; //IPV4
    serveraddr.sin_port = htons(atoi(argv[1]));//port
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
                      
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

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while (1) {
        //���̸߳������acceptȥ��ÿͻ��˵�����
        int fd = accept(sockfd, NULL, NULL);
        if (fd < 0) {

            perror("accept error");
            continue;
        }

        /*
        5���������߳�ȥ����IO����(read/write) ��
        ���ӵĿͻ��˽���˫���ͨ��

        ���ַ�ʽ Ĭ��״̬������״̬
        pthread_join �������ȴ����߳̽������ͷ��߳���Դ

        ������ һ�㲻���˳�
        ��������
        */

        pthread_t threadId;
        int err;
        //�Է���״̬�������߳�
        if ((err = pthread_create(&threadId, &attr, th_fn, (void*)&fd)) != 0) {

            perror("pthread_create error");
        }
        pthread_attr_destroy(&attr); //���߳�ȥ��attr����
    }

    return 0;
}