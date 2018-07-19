#include <stdio.h>
int main(){
    int i,j;       //定义变量的时候，需要给变量赋初值，不然为乱码 
    printf("15 %% 7 = %d\n",15 %7);
    i = j = 7;
    printf("i是%d,j是%d\n",i,j);
    i += 2;       //相当于i = i + 2
    printf("i是%d\n",i);
    i *= 2 + 3;   //*=使它的优先级降低
    printf("i是%d\n",i);
    return 0;

}

