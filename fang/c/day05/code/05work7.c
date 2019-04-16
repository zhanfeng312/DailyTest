/*
 *
 * scanf练习
 */
# include <stdio.h>
int main(){
    int shu_zi = 0,shu_zi1 = 0;
    printf("请输入两个整数：");
    scanf("abc%d def%d",&shu_zi,&shu_zi1);   //使用scanf函数输入数据时，必须按格式输入
  //  scanf("%d",shu_zi);     段错误
    printf("%d %d\n",shu_zi,shu_zi1);


    return 0;
}
