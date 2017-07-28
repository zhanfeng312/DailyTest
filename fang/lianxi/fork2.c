#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main (void){
    pid_t pid;
    char *message;
    int n;
    pid = fork();
    switch (pid)
    {
        case -1:
            perror("forkerror");
            exit(1);
        case 0:
            message = "I am the child";
            n = 5;
            break;
        default:
            message = "I am the parent";
            n = 5;
            break;
    }
    while(n > 0)
    {
        printf("%s", message);
        printf("my process id is %d\n", getpid());
        n--;
        sleep(1);
    }
    return 0;
}
