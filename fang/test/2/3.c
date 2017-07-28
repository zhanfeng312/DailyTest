#include <stdio.h>
#include <stdlib.h>
void find(int a[3][3], int m) {
    int i;
    for (i = 0; i < 3;i++) {
        if (m <= a[i][2]){  //和每一行的最后一个元素比较
            int n = binFind(a[i], 3 , m);
            if (n == -1) //没找到,跳到下一行
                continue;
            else{
                printf("已经找到,该元素的下标为[%d,%d]\n", i, n);
                exit(0);
            }
        }
        else
            continue;
    }
    printf("没找到!\n");
}
int binFind(int data[], int size, int key){
    int left = 0;
    int right = size -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (key > data[mid])
            left = mid + 1;
        else if (key < data[mid])
            right = mid - 1;
        else 
            return mid;
    }
    return -1;
}
int main (void) {
    int a[3][3] = {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}};
    int value;
    printf("请输入要查找的数:");
    scanf("%d", &value);
    find(a, value);
    return 0;
}
