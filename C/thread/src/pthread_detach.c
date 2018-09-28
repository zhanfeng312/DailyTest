#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void out_state(pthread_attr_t *attr)
{
    int state;

    if (pthread_attr_getdetachstate(attr, &state) != 0) {
        perror("getdetachstate error");
    }
    else {
        if (state == PTHREAD_CREATE_JOINABLE) {
            printf("joinable state\n");
        }else if (state == PTHREAD_CREATE_DETACHED) {
            printf("detach state\n");
        }else {
            printf("error state\n");
        }
    }
}

void *th_fn(void *arg)
{
    int i;
    int sum = 0;
    for (i = 1; i <= 100; i++)
        sum += i;
    return (void*)sum;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t default_th, detach_th;

    //�����߳�����
    pthread_attr_t attr;
    //���߳����Գ�ʼ��
    pthread_attr_init(&attr);
    //����߳�����
    out_state(&attr);

    //ȡ�������Ե�Ĭ��ֵ����������ʽ�������߳�
    if ((err = pthread_create(&default_th, &attr, th_fn, (void*)0)) != 0) {
        perror("pthread_create err");
        exit(1);
    }

    int *res;
    if ((err = pthread_join(default_th, (void**)&res)) != 0) {
        perror("pthread_join error");
    }else {
        printf("default return value is %d\n", (int)res);
    }

    printf("------------------------------------\n");

    //���÷�������Ϊ����״̬����
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    out_state(&attr);

    //�Է���״̬�������߳�
    if ((err = pthread_create(&detach_th, &attr, th_fn, (void*)0)) != 0) {
        perror("pthread_create err");
        exit(1);
    }

    //�����߳�����
    pthread_attr_destroy(&attr);
    sleep(1);
    printf("0x%lx finished!\n", pthread_self());

    return 0;
}