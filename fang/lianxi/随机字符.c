#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    srand((time(NULL)));
    char a[10],x;         //要存放目标字符的数组
    int i,j;
    for(i = 0;i <= 3;i++){
        x = rand() % 26 + 97;
        for(j = 0;j <= i;j++){
            if(a[j] != x)
                a[i] = x;
            else{

                x = rand() % 26 + 97;
                while(x == a[j])
                    x = rand() % 26 +97;
            }
        }
    }
    for(i = 0;i <= 3;i++)
    {
        printf("%c ",a[i]);
    }
    printf("\n");
    return 0;
}
