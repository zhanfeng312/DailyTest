#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    printf("%lu\n", sizeof(pthread_t));
    char buf[64] = { 0 };
    sscanf("1234ABCabc", "%[1-9a-z]", buf);

    printf("%s\n", buf);
    return 0;
}