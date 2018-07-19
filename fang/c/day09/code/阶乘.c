#include <stdio.h>
int jiecheng(int num)
{
    if(num == 0 || num == 1){
        return 1;
    }
    else{
        return num * jiecheng(num - 1);
    }
}
int main(){
    int num = 0;
    printf("输入一个整数:");
    scanf("%d",&num);
    printf("%d!是%d\n",num,jiecheng(num));
    return 0;
}
