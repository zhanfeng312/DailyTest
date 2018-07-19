#include<stdio.h>
int main(){
    int shu_zi = 0;
    printf("请输入一个整数：");
    scanf("%d",&shu_zi);
    if ( shu_zi % 2){
       printf("奇数\n");
    }
    else {
       printf("偶数\n");
    }

   if (!(shu_zi % 5)){    
       printf("能被5整除");
   }
   /*
   if (!(shu_zi % 5) && (shu_zi % 2)){    
       printf("能被5整除\n");
   }*/

    return 0;

}
