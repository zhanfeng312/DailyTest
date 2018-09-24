#include "account.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char     name[20];
    Account *account;
    double   amt;
}OperArg;

//取款
void *withdraw_fn(void *arg)
{
    OperArg *oa = (OperArg*)arg;
    double amt = withdraw(oa->account, oa->amt);

    printf("%s(%lu) withdraw %f from account %d\n",
            oa->name, pthread_self(), amt, oa->account->code);
    
    return (void*)0;
}

//存款
void *deposit_fn(void *arg)
{
    OperArg *oa = (OperArg*)arg;
    double amt = deposit(oa->account, oa->amt);

    printf("%s(%lu) deposit %f from account %d\n",
            oa->name, pthread_self(), amt, oa->account->code);
    
    return (void*)0;
}


//定义检查银行账户的线程运行函数
void *check_fn(void *arg)
{
    
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t boy_thid, girl_thid;
    Account *a = create_account(100001, 10000);

    OperArg o1, o2;
    strcpy(o1.name, "boy thread");
    o1.account = a;
    o1.amt = 10000;

    strcpy(o2.name, "girl thread");
    o2.account = a;
    o2.amt = 10000;

    //启动两个子线程(boy和girl 线程)
    //同时去操作同一个银行账户
    if ((err = pthread_create(&boy_thid, NULL,
                    withdraw_fn, (void*)&o1)) != 0){
        perror("pthread create error");
    }
    if ((err = pthread_create(&girl_thid, NULL,
                    withdraw_fn, (void*)&o2)) != 0){
        perror("pthread create error");
    }

    pthread_join(boy_thid, NULL);
    pthread_join(girl_thid, NULL);

    printf("account balance: %f\n", get_balance(a));

    destroy_account(a);
    
    return 0;
}
