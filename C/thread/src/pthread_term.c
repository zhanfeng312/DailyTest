#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int d1;
    int d2;
}Arg;

void *th_fn(void *arg)
{
    Arg *r = (Arg*)arg;

    return (void*)(r->d1 + r->d2);
    //return (void*)r;
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t th;
    Arg r = {20, 50};

    if ((err = pthread_create(&th, NULL, th_fn, (void*)&r)) != 0){

        perror("pthread_create error");
    }
    
    /*
        pthread_join(..., int **p)
        *p = 70 ---> result = 70
    */
    int *result;
    pthread_join(th, (void**)&result);
    printf("result is %d\n", (int)result);


    /*
        int result;
        pthread_join(th, (void*)&result);
        printf("result is %d\n", result);
    */

    /*
        int *result;
        pthread_join(th, (void**)&result);
        printf("result is %d\n", ((Arg*)result)->d1 + ((Arg*)result)->d2);
    */

    return 0;
}