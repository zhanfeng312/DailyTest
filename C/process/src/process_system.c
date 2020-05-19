#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *cmd1 = "date > s1.txt";
const char *cmd2 = "date > s2.txt";

void my_system(const char *cmd)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        if (execlp("/bin/bash", "/bin/bash", "-c", cmd, NULL) < 0) {
            perror("execlp error");
            exit(1);
        }
    } else {
        wait(0);
    }
}

int main(void)
{
    system("clear");

    system(cmd1);
    my_system(cmd2);

    return 0;
}