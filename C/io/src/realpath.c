#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    char buf[128]= {0};
    if (realpath("./a.txt.soft1", buf) == NULL) { //规范化路径，返回绝对路径
        if (errno == ENOENT) {
            printf("The file not exist\n");
        } else {
            perror("realpath error");
        }
        exit(1);
    }
    printf("%s\n", buf);
    return 0;
}