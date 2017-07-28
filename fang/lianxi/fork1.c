#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main (void){
    pid_t pid;
    pid = fork();
    switch(pid)
    {
        case -1:
            perror("forkerror");
            exit(1);
        case 0:
            printf("I am the child process%d\n", getpid());
            break;
        default:
            printf("I am the parent process%d\n", getpid());
            break;
    }
    return 0;
}
