#include<stdio.h>
int main(){
    int shu_zi = 0;
    printf("请输入0~2之间的一个整数:");
    scanf("%d",&shu_zi);
    switch (shu_zi % 3) {
        case 0:        //shu_zi = 1的处理部分
               printf("红\n");
               break;
        case 1:
               printf("黄\n");
               break;
        case 2:
               printf("蓝\n");
               break;
        default :
               printf("输入的数不符合要求\n");
               break;
    
    }
       return 0;
}
