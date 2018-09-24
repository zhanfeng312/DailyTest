#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <pthread.h>

typedef struct 
{
    int    code;
    double balance;

    //定义一把互斥锁，用来对多线程操作的
    //银行账户(共享资源)进行加锁（保护）的作用
    /*
        建议互斥锁用来锁定一个账户，和账户绑定在一起
        尽量不设置成全局变量，否则可能出现一把锁去
        锁几百个账户，导致并发性能降低
    */
    //pthread_mutex_t mutex;
    //定义读写锁
    pthread_rwlock_t rwlock;
}Account;


//创建账户
extern Account* create_account(int code, double balance);
//销毁账户
extern void destroy_account(Account *a);
//取款
extern double withdraw(Account *a, double amt);
//存款
extern double deposit(Account *a, double amt);
//查看账户余额
extern double get_balance(Account *a);

#endif
