#include <stdio.h>
#include <unistd.h>

int main(void)
{
    /*
        l: 参数以可变参数形式传递, NULL结尾
        v：参数以指针数组形式传递, NULL结尾
        带p的函数：第一个路径参数可写相对路径，在PATH路径下找命令
        待e的函数：要指定环境表
    */
#if 0
    int ret = execl("/bin/ls", "ls", "-l", NULL); //使用新进程替换当前进程
    int ret = execlp("ls", "ls", "-l", NULL);
    int rey = execv("/bin/ls", argv1);
    int ret = execvp("ls", argv1);
    int ret = execle("process_env", "process_env", "abc", "123", NULL, envir);
#endif
    char *argv1[] = {"ls", "-l", NULL};
    char *argv2[] = {"process_env", "abc", "123", NULL};
    char *envir[] = {"CITY=XI'AN", "PATH=/fangzhf", NULL};
    int ret = execve("process_env", argv2, envir);
    if (ret == -1) {
        perror("execl failed.");
        return -1;
    }
    return 0;
}