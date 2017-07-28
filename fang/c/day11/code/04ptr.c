#include <stdio.h>
#include <string.h>
int main(){
    char buf[10];
    memset(buf, 0, 10); //内存设置
    int i;
    for (i = 0; i < 10; i++)
        printf("%c ", buf[i]);
    /*printf("请输入一个字符串:");
    //scanf("%s",buf);
    fgets(buf, 10, stdin);  //stdin表示从键盘输入，只输入9个字
    printf("%s\n",buf);*/
    return 0;
}
