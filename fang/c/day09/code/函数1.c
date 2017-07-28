#include<stdio.h>
int read(){
    int value = 0;
    printf("请输入一个整数:");
    while(!scanf("%d",&value)){
        scanf("%*[^\n]");
        scanf("%*c");
    printf("请再输入一个整数:");
    }
    scanf("%*[^\n]");
    scanf("%*c");
    return value;
}

int main(){
    int value = 0;
    value = read();
    printf("数字是%d\n",value);

    return 0;
}
