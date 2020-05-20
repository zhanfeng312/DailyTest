#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

typedef struct {
    long    type;//��Ϣ����
    int     start;//��Ϣ���ݱ���(����start �� end)
    int     end;
}MSG;

/*
   ����Ϣ�����з�����Ϣ
*/
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s key\n", argv[0]);
        exit(1);
    }

    key_t key = atoi(argv[1]);
    //key_t key = IPC_PRIVATE;
    //key_t key = ftok(argv[1], 0);//���ݴ������Ĳ�������
    printf("key: %d\n", key);

    //������Ϣ����
    int msq_id;
    if ((msq_id = msgget(key, IPC_CREAT | IPC_EXCL | 0777)) < 0) {
        perror("msgget error");//ͷ�ļ�
    }
    printf("msq id: %d\n", msq_id);

    //����Ҫ���͵���Ϣ
    MSG m1 = {4, 10, 100};

    //������Ϣ����Ϣ����
    if (msgsnd(msq_id, &m1, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0) {
        perror("msgsnd error");
    }

    //����Ϣ��������Ϣ������
    struct msqid_ds ds;
    if (msgctl(msq_id, IPC_STAT, &ds) < 0) {
        perror("msgctl error");
    }
    printf("msg total: %ld\n", ds.msg_qnum);

    exit(0);
}