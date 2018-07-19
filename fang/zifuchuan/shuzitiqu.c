#include <stdio.h>
#include <stdlib.h>
void shuzitiqu(char *p)
{
    if (p == NULL){
        printf("当前字符串为空\n");
        exit(0);
    }
    char *src = NULL;
    int len = 0;      //记录数字串的长度
    while (*p != '\0'){
        if (*p >= '0' && *p <= '9'){ //满足条件进入这个分支,否则p++;
            src = p;
            for (;(*p >= '0' && *p <= '9');p++){
                len++;
            }
            src[len] = '\0'; //给最后赋'\0'
            printf("%s", src);
            printf("\t对应的数字为:%u\n", atoi(src));
            len = 0;
        }
            p++;
    }
}
int main(void){
    char p[] = "abc123d456789";
    shuzitiqu(p);
    return 0;
}
