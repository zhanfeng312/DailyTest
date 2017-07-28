#include <stdio.h>
int main ()
{
    int i = 0,j, k = 1, m=0;//i,j为两个循环变量,m记录数组b的元素个数
    int a[] = {1, 2, 5, 8, 10, 4, 3, 6, 9, 7};
    int b[10] = {0};
    for (i = 0;i < 10; i++){ 
        if (a[i] == k){
            printf("%d ", a[i]);
            for (j = 0; j < m;){
                if(b[j] != (k+1))
                    j++;
                else{
                    printf("%d ", b[j]);
                    j = 0;
                    k++;
                }
            }
            printf("\n");
            k++;
        }
        else
            b[m++]= a[i];//给数组b赋值
        }
}
        
            

