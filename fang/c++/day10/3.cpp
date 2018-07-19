#include <iostream>
using namespace std;
//基本思想是选出未排序序列的最小值，插入到已排好序列的末尾
void selectSort(int data[], size_t size) {
    size_t k,temp;  //k为最小元素的下标,temp为中间变量
    for(size_t i = 0; i < size - 1;i++){
        k = i; //先使i为最小元素下标,以后再判断
        for(size_t j = i+1;j < size;++j)
            if (data[j] < data[k])
                k = j;
        if (k != i){
            temp = data[k];
            data[k] = data[i];
            data[i] = temp;
        }
    }
}
int main(void) {
    int arr[] = {50, 40, 30, 20, 10};
    selectSort(arr, 5);
    for(size_t i = 0;i < 5;++i)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
