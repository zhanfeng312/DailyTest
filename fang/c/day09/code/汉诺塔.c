/*
 * 递归练习
 */
#include <stdio.h>
void han(int num,char src ,char mid, char dest)   //三个盘
{
    if(num == 1){
    printf("把盘子%d从%c柱移动到%c柱\n",num,src,dest);
    }
    else{
    han(num - 1,src,dest,mid);
    printf("把盘子%d从%c柱移动到%c柱\n",num,src,dest);
    han(num -1,mid, src, dest);

    }

}
int main(){
    int num = 0;
    printf("请输入盘子个数：");
    scanf("%d",&num);
    han(num,'A','B','C');
    return 0;
}
