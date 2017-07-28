#include<stdio.h>
int main(){
    int hua_ban = 0,xun_huan = 0,biao_zhi = 0;
    printf("请输入花瓣数:");
    scanf("%d",&hua_ban);
    /*
    for(xun_huan = 0;xun_huan < hua_ban ;xun_huan++){
        if(biao_zhi ){
        printf("She loves me!\n");
        }
        else{
            printf("She doesn't love me!\n");
        }
        biao_zhi = 1 -biao_zhi;

    }
    */
    for(xun_huan = hua_ban;xun_huan >= 1;xun_huan--){
        if(xun_huan % 2){
            printf("爱我\n");
        }

        else{
            printf("不爱我\n");
        }
                
    }
    return 0;
}
