#include <stdio.h>
void square(int a[],int num){
    int loop = 0;
    for(loop = 0;loop <= num-1;loop++){
        a[loop] *= a[loop];   
    }
}
int main(){
    int a[] ={4,5,9},loop = 0;
    square(a,3);                     //3代表数组中变量的个数
    for(loop = 0;loop <= 2;loop++){
        printf("%3d",a[loop]);
    }
    printf("\n");

    return 0;
}
