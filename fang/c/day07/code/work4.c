/*
 *
 *素数练习
 * 
*/
#include<stdio.h>
#include<math.h>
int main(){
    int shu_zi = 0,xun_huan = 0,gen = 0;
    printf("请输入一个整数:");
    scanf("%d",&shu_zi);
    gen = sqrt(shu_zi);       //两种结束可能
    for(xun_huan = 2;xun_huan <= gen;xun_huan++){
        if(shu_zi % xun_huan == 0 ){
            break;
        }
  }
    if(xun_huan <= gen)
        printf("该数不是素数\n");
    else 
        printf("该数是素数\n");

    return 0;
}
