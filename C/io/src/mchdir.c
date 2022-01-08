#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s dir\n", argv[0]);
        exit(1);
    }

    char buf[1024];
    memset(buf, 0, sizeof(buf));
    //获得当前的工作目录
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("current dir: %s\n", buf);
    }

    //切换目录
    if (chdir(argv[1]) < 0) {
        perror("chdir error");
        exit(1);
    }
    memset(buf, 0, sizeof(buf));
    //获得切换后的工作目录
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("current dir: %s\n", buf);
    }

    return 0;
}