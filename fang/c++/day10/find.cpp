#include <iostream>
using namespace std;
int binFind (int data[], int size, int key) {  //二分查找
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (key > data[mid])
            left = mid + 1;
        else if (key < data[mid])
            right = mid - 1;
        else
            return mid;
    }
    return -1;  //没找到
}
int main(void) {
    int arr[3] = {2, 7, 8};
    size_t size = sizeof (arr) / sizeof (arr[0]);
    size_t i = binFind(arr, 3, 8);
    cout << i << endl;
    return 0;
}
    
      

