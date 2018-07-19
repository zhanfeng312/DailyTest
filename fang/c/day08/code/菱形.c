#include <stdio.h>
int main(){
    int i,j;
    for(i = 0;i < 5;i++){
        for(j = 0;j <= (3-i);j++) //先打印空格
            printf(" ");
        for(j = 4-i;j <= (4+i);j++)//再是*号
            printf("*");
        printf("\n");
    }
    for (i = 0;i < 4;i++){
        for (j = 0;j < i + 1; j++)
            printf(" ");
        for (j = i;j <= 6 - i;j++)
            printf("*");
        printf("\n");
    }
    return 0;
}

