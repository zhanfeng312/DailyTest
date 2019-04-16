#include<stdio.h>
int main(){
    int i = 0;
    for(i = 0;i <= 25;i++)
    {
        if(i*4 + (35 -i)*2 == 100)
            printf("鸡有%d,兔有%d\n",35 - i,i);
    }
    return 0;
}
