#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <pthread.h>

typedef struct 
{
    int    code;
    double balance;

    //����һ�ѻ������������Զ��̲߳�����
    //�����˻�(������Դ)���м�����������������
    /*
        ���黥������������һ���˻������˻�����һ��
        ���������ó�ȫ�ֱ�����������ܳ���һ����ȥ
        �����ٸ��˻������²������ܽ���
    */
    //pthread_mutex_t mutex;
    //�����д��
    pthread_rwlock_t rwlock;
}Account;


//�����˻�
extern Account* create_account(int code, double balance);
//�����˻�
extern void destroy_account(Account *a);
//ȡ��
extern double withdraw(Account *a, double amt);
//���
extern double deposit(Account *a, double amt);
//�鿴�˻����
extern double get_balance(Account *a);

#endif
