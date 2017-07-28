# include <stdio.h>
int main(){
    int i = 0;
    printf("请输入一个数:");
    scanf("%d",&i);
    if (i > 0){
        printf("该数非负!\n");
    }
    else if (i < 0){
        printf("该数为负数!\n");
    }
    else (0 == i){
        printf("零\n");
    }
    return 0;
}
