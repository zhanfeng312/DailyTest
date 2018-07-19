/*
 *位操作符
 *
 */
# include<stdio.h>
int main(){
     printf("3 & 5 是%d\n", 3 & 5);         //0000 0011
     printf("3 | 5 是%d\n",3 | 5);          //0000 0101
     printf("3 ^ 5 是%d\n",3 ^ 5);
     printf("~0xffffff96是0x%x\n",~0xffffff96);
   /*int shu_zi = 0;
   scanf("%d",&shu_zi);
   if (!(shu_zi & 1)== 0)
       printf("为奇数\n");
   else 
       printf("为偶数\n");
       */
       


    return 0;
}
