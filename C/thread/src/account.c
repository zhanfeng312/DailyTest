#include "account.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>



//�����˻�
Account* create_account(int code, double balance)
{
    Account *a = (Account*)malloc(sizeof(Account));
    assert(a != NULL);
    
    a->code = code;
    a->balance = balance;
    //�Ի��������г�ʼ��
    //pthread_mutex_init(&a->mutex, NULL);

    //�Զ�д�����г�ʼ��
    pthread_rwlock_init(&a->rwlock, NULL);

    return a;
}

//�����˻�
void destroy_account(Account *a)
{
    assert(a != NULL);
    //���ٻ�����
    //pthread_mutex_destroy(&a->mutex);

    //���ٶ�д��
    pthread_rwlock_destroy(&a->rwlock);
    free(a);
}


//ȡ��
double withdraw(Account *a, double amt)
{
    assert(a != NULL);

    //�Թ�����Դ�������ٽ���
    //pthread_mutex_lock(&a->mutex);//�Թ�����Դ���˻�������
    //��д��
    pthread_rwlock_wrlock(&a->rwlock);

    if (amt < 0 || amt > a->balance){
        
        //�ͷŻ�����
        //pthread_mutex_unlock(&a->mutex);
        //�ͷ�д��
        pthread_rwlock_unlock(&a->rwlock);
        return 0.0;
    }

    double balance = a->balance;
    sleep(1);
    balance -= amt;
    a->balance = balance;

    //�ͷŻ�����
    //pthread_mutex_unlock(&a->mutex);
    //�ͷ�д��
    pthread_rwlock_unlock(&a->rwlock);

    return amt;
}

//���
double deposit(Account *a, double amt)
{
    assert(a != NULL);

    //pthread_mutex_lock(&a->mutex);
    pthread_rwlock_wrlock(&a->rwlock);

    if (amt < 0){
        //pthread_mutex_unlock(&a->mutex);
        pthread_rwlock_unlock(&a->rwlock);
        return 0.0;
    }

    double balance = a->balance;
    sleep(1);
    balance += amt;
    a->balance = balance;

    //pthread_mutex_unlock(&a->mutex);
    pthread_rwlock_unlock(&a->rwlock);

    return amt;
}

//�鿴�˻����
double get_balance(Account *a)
{
    assert(a != NULL);

    //pthread_mutex_lock(&a->mutex);
    pthread_rwlock_rdlock(&a->rwlock);

    double balance = a->balance;

    //pthread_mutex_unlock(&a->mutex);
    pthread_rwlock_unlock(&a->rwlock);

    return balance;
}
