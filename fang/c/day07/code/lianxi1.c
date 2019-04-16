#include <stdio.h>
int main(){
    int xun_huan = 0,shu_zi = 0,he = 0;
    for(xun_huan = 0;xun_huan < 3;xun_huan++){
        printf("请输入一个数字:");
        scanf("%d",&shu_zi);
        he += shu_zi;  //复合运算符
    }
    printf("求和结果是%d\n",he);
    return 0;
}
/*
 * xun_huan = 0
 * xun_huan < 3
 *
 * {}
 * xun_huan++
 * xun_huan < 3
 *
 * {}
 * xun_huan++
 * xun_huan < 3
 *
 * {}
 * xun_huan++
 * xun_huan < 3
 * */
