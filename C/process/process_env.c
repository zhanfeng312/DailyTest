#include <stdio.h>

/* environ变量是一个char** 类型，存储着系统的环境变量 */
extern char **environ;
/*
    进程启动时，都有一个独立的环境表，初始的环境表继承自父进程
    环境表本质就是一个指针数组，遍历数组即可
*/
int main(int argc, char *argv[])
{
    int i = 0;
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}