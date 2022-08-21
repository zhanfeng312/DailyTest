#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = popen("cat /etc/passwd", "r");
    if (fp == NULL) {
        printf("popen failed\n");
        exit(1);
    }

    char buf[512] = {0};
    while (1) {
       if (fgets(buf, sizeof(buf), fp) == NULL) {
           if (feof(fp)) { //读到了文件尾
               break;
           }
           if (ferror(fp)) {
               printf("read error\n");
               break;
           }
       } else {
           printf("%s", buf);
       }
    }
    int status = pclose(fp);
    printf("status is %d\n", status);
    if (WIFEXITED(status)) {
        printf("%d\n", WEXITSTATUS(status));
    }
    return 0;
}