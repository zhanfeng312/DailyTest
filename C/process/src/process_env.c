#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void show_env()
{
    int i = 0;
    char *env = NULL;
    while ((env = environ[i]) != NULL) {
        printf("%s\n", env);
        i++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    /*
    int i = 0;
    char *env = NULL;
    while((env = envp[i]) != NULL) {
        printf("%s\n", env);
        i++;
    }
    */

    show_env();
    printf("-----------------------\n");
    putenv("CITY=jinan");
    setenv("COMPANY", "inspur", 1);
    show_env();
    printf("-----------------------\n");
    unsetenv("CITY");
    show_env();
}