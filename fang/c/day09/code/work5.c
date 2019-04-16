/*
 *二维数组练习
 */
#include <stdio.h>
int main(){
    int arr[][4] = {{1,2},{5,6,7,8},{6,7,8,9}};
    /*int arr[][4] = {{1},
                    {0,1},
                    {0,0,1},
                    {0,0,0,1}};*/
    int row = 0,col = 0;
   /* int arr[4][4] = {0};
    for(row = 0;row <= 3;row++){
        arr[row][row] = 1;
    }*/
    for(row = 0;row <= 2;row++){
        for(col = 0;col <= 3;col++){
            printf("%d ",arr[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
