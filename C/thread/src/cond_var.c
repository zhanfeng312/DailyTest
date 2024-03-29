#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

struct msg {
    int num;
    struct msg *next;
};

struct msg *head = NULL;
struct msg *mp = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

static void *producter(void *arg)
{
    while (1) {
        mp = (struct msg *)malloc(sizeof(struct msg));
        mp->num = rand() % 400 + 1;
        printf("-------producted ----%d\n", mp->num);

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);
        sleep(rand() % 3);
    }
    return NULL;
}

static void *consumer(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        while (head == NULL) { //消费者可能有多个
            pthread_cond_wait(&has_product, &mutex);
        }
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&mutex);
        printf("------consumer----%d\n", mp->num);
        free(mp);
        mp = NULL;
        sleep(rand() % 3);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    srand(0);
    pthread_t ptid, ctid;

    pthread_create(&ptid, NULL, producter, NULL);
    pthread_create(&ctid, NULL, consumer, NULL);

    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);

    return 0;
}