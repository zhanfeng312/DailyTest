#include <stdio.h>
#include <stdlib.h>
int main(){
    int loop = 0;
    int *p_value = (int *)malloc(4 * sizeof(int));
    if(p_value){
        printf("请输入四个整数:");
        for(loop = 0;loop <= 3;loop++){
            scanf("%d",p_value + loop);
        }

        printf("逆序结果为:");
        for(loop = 3;loop >= 0;loop--){
            printf("%d ",*(p_value + loop));
        }
        printf("\n");
        free(p_value);
        p_value = NULL;
    }
    return 0;
}
