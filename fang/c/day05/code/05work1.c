/*
    变量练习
*/
# include <stdio.h>
int main(){
    int shu_zi;
    shu_zi = 3000;
    // 3000 = shu_zi;    错误，3000不能当作变量使用
    shu_zi = shu_zi;   //这两个变量不一样。是当数字用还是变量用。
    printf("%d\n",shu_zi);

    return 0;
}

