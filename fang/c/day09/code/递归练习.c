#include <stdio.h>
void show(int num)
{
    if(num == 1){
        printf("1\n");
    }
    else{
        printf("%d\n",num);
        show(num - 1);
    }
}
int main(){
    int num = 0;
    printf("input a number:");
    scanf("%d",&num);
    show(num);
    return 0;
}
