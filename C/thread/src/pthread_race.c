#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//�����߳����к���
void *th_fn(void *arg)
{
    int distance = (int)arg;
    int i;
    for (i = 1; i <= distance; i++) {
        printf("0x%lx run %d\n", pthread_self(), i);
        int time = (int)(drand48() * 100000);
        usleep(time); //΢��
    }
    return (void*)0;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t rabbit, turtle; //�����̱߳�ʶ��

    //����rabbit�߳�
    if ((err = pthread_create(&rabbit, NULL, th_fn, (void*)50)) != 0) {
        perror("pthread_create error");
    }
    //����turtle�߳�
    if ((err = pthread_create(&turtle, NULL, th_fn, (void*)50)) != 0) {
        perror("pthread_create error");
    }

    //sleep(10);

    //�����̵߳���pthread_join()���Լ�������
    //ֱ��rabbit��turtle�߳̽�����������
    pthread_join(rabbit, NULL);
    pthread_join(turtle, NULL);

    printf("control thread id: 0x%lx\n", pthread_self());
    printf("finished!\n");

    return 0;
}