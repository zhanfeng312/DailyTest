/*
 *循环嵌套练习
 *
 */
#include <stdio.h>
int main(){
    int xun_huan = 0,xun_huan1 = 0;  //xuan_huan 是行号(从0开始)
    for(xun_huan = 0;xun_huan <= 5;xun_huan++){
        for(xun_huan1 = 0;xun_huan1 <= xun_huan;xun_huan1++)
        {
            printf("%d",xun_huan1);
        }
        printf("\n");
    }
              return 0;
}

