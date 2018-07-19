#include <stdio.h>
void neg(int value[],int num){
    //printf("sizeof(value)是%d\n",sizeof(value));
    int loop = 0;
    for(loop = 0;loop <= num-1;loop++){
        value[loop] = 0 -value[loop];
    }
}

int main(){
    int value[] = {4,-7,9,8},loop = 0;
    neg(value,4);
    for(loop = 0;loop <= 3;loop++){
        printf("%5d",value[loop]);
    }
    printf("\n");
    return 0;
}
