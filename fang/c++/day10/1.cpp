#include <iostream>
using namespace std;
//快速排序
void quickSort (int data[], size_t left, size_t right) {
    size_t p = (left + right)/2;  //p为基准下标
    int pivot = data[p]; //把值记录下来
    for (size_t i = left,j = right; i < j;) {
        while (i <= p && data[i] < pivot)
            ++i;
        if (i < p){
            data[p] = data[i];
            p = i;
        }
        while (j >= p && data[j] > pivot)
            --j;
        if (j > p) {
            data[p] = data[j];
            p = j;
        }
    }
    data[p] = pivot;
    //递归
    if (p - left > 1)
        quickSort (data, left, p - 1);
    if (right - p > 1)
        quickSort (data, p + 1, right);
}
int main(void) {
    int arr[] = {50, 80, 40, 10, 20};
    size_t size = sizeof (arr) / sizeof (arr[0]);
    quickSort (arr, 0, size - 1);
    for(size_t i = 0;i < size ;++i)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
