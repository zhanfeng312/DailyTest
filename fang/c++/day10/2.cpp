#include <iostream>
using namespace std;
//基本思想是把要排的元素插入到合适的位置，当然主要还是找位置的步骤
void insertSort (int data[], size_t size) {
    for(size_t i = 1;i < size;i++) {  //插入元素的下标，从1开始
        int temp = data[i]; //把要插的这个值先记录下来
        size_t j;
        for(j = i;j > 0&&data[j-1] > temp;j--){ //依次与前面的元素比较，找到合适的插入位
            data[j] = data[j-1];
        }
        if(j != i)  //满足条件，把这个值放到合适位置,j就为要插入的位置
            data[j] = temp;
    }
}
int main(void) {
    int arr[] = {50, 40, 30, 20, 10};
    insertSort(arr, 5);
    for(size_t i = 0;i < 5;++i)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
