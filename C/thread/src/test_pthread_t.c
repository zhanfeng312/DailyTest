#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    printf("%lu\n", sizeof(pthread_t));

    return 0;
}
