#include<stdio.h>
int main(){
   /* int yi = 0,er = 0,wu = 0;
    printf("总共有：\n");
    
    for(yi = 0;yi <= 10;yi++){
        for(er = 0;er <= 5;er++){
            for(wu = 0;wu <= 2;wu++){
                if(yi + er*2 +wu*5 == 10){
                  printf("%d,%d,%d\n",yi,er,wu); 
                }
            }
        }
    }*/
    int xun_huan = 0,ge_shu = 0,xun_huan1 = 0;
    for(xun_huan = 0;xun_huan <= 2;xun_huan++){
        ge_shu = (10-5*xun_huan)/2;
        for(xun_huan1 = 0;xun_huan1 <= ge_shu;xun_huan1++){
            printf("五元%d张，两元%d张，一元%d张\n",xun_huan,xun_huan1,10 -xun_huan-xun_huan1);
        }
    }
    return 0;
}
