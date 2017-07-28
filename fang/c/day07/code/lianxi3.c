#include<stdio.h>
int main(){
    int xun_huan = 0,sum = 0;
    for(xun_huan = 5;xun_huan <= 20;xun_huan++){
        if (xun_huan == 7){
            continue;
        }
        sum += xun_huan;
        if(sum > 40){
            break;
        }
    }
        printf("xun_huan是%d，sum是%d\n",xun_huan,sum);

    return 0;

}
