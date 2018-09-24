#include "account.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>



//创建账户
Account* create_account(int code, double balance)
{
    Account *a = (Account*)malloc(sizeof(Account));
    assert(a != NULL);
    
    a->code = code;
    a->balance = balance;
    //对互斥锁进行初始化
    //pthread_mutex_init(&a->mutex, NULL);

    //对读写锁进行初始化
    pthread_rwlock_init(&a->rwlock, NULL);

    return a;
}

//销毁账户
void destroy_account(Account *a)
{
    assert(a != NULL);
    //销毁互斥锁
    //pthread_mutex_destroy(&a->mutex);

    //销毁读写锁
    pthread_rwlock_destroy(&a->rwlock);
    free(a);
}


//取款
double withdraw(Account *a, double amt)
{
    assert(a != NULL);

    //对共享资源操作的临界区
    //pthread_mutex_lock(&a->mutex);//对共享资源（账户）加锁
    //加写锁
    pthread_rwlock_wrlock(&a->rwlock);

    if (amt < 0 || amt > a->balance){
        
        //释放互斥锁
        //pthread_mutex_unlock(&a->mutex);
        //释放写锁
        pthread_rwlock_unlock(&a->rwlock);
        return 0.0;
    }

    double balance = a->balance;
    sleep(1);
    balance -= amt;
    a->balance = balance;

    //释放互斥锁
    //pthread_mutex_unlock(&a->mutex);
    //释放写锁
    pthread_rwlock_unlock(&a->rwlock);

    return amt;
}

//存款
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

//查看账户余额
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
