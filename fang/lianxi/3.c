#include <stdio.h>
int func(int);
int func (int x) {  //用来求有多少个1的函数
    int count = 0;
    while (x) {
        count ++;
        x = x & (x - 1);
    }
    return count;
}
int main (){
    int value = func(9999);
    printf("value = %d\n", value);
    return 0;
}
