#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void signal_handler(int signum){

    printf("receive signal %d\n", signum);
    exit(1);
}

int main(int argc, char **argv) 
{
    struct sigaction sa;
	sa.sa_flags = 0;

    sa.sa_handler = signal_handler;
    sigaction(SIGBUS, &sa, NULL);

    printf("123\n");

    int *iptr = NULL;
    char *cptr = NULL;
    
    /* malloc() always provides aligned memory */
    cptr = malloc(sizeof(int) + 1);

    /* Increment the pointer by one, making it misaligned */
    iptr = (int *) ++cptr;

    /* Dereference it as an int pointer, causing an unaligned access */
    *iptr = 42;
    
    return 0;
}