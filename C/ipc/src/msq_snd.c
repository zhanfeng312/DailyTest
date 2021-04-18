#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

typedef struct {
    long    type;//消息类型
    int     start;//消息数据本身(包括start 和 end)
    int     end;
}MSG;

/*
   往消息队列中发送消息
*/
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s key\n", argv[0]);
        exit(1);
    }

    key_t key = atoi(argv[1]);
    //key_t key = IPC_PRIVATE;
    //key_t key = ftok(argv[1], 0);//根据传进来的参数计算
    printf("key: %d\n", key);

    //创建消息队列
    int msq_id;
    if ((msq_id = msgget(key, IPC_CREAT | IPC_EXCL | 0777)) < 0) {
        perror("msgget error");//头文件
    }
    printf("msq id: %d\n", msq_id);

    //定义要发送的消息
    MSG m1 = {4, 10, 100};

    //发送消息到消息队列
    if (msgsnd(msq_id, &m1, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0) {
        perror("msgsnd error");
    }

    //得消息队列中消息的总数
    struct msqid_ds ds;
    if (msgctl(msq_id, IPC_STAT, &ds) < 0) {
        perror("msgctl error");
    }
    printf("msg total: %ld\n", ds.msg_qnum);

    exit(0);
}