#include <stdio.h>
#include <string.h>
int main(){
    char str1[20];
    int i = 0;
    for(i = 0;i < 3;i++){
        printf("请输入用户名:");
        fgets(str1, 10, stdin);
        if(strcmp(str1,"admin\n") != 0 ) {
            continue;
        }
        printf("请输入密码:");
        fgets(str1,10,stdin);
        if(strcmp(str1, "123456\n") == 0) {
            break;
        }
    }
    if(i < 3)
        printf("登陆成功!\n");
    else
        printf("登陆失败\n");
    return 0;
}
