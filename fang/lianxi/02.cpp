#include <iostream>
using namespace std;
int add(int a, int b){
    if (0 == b)//没有进位的时候就完成运算
        return a;
    int sum, carry;
    sum = a ^ b; //完成没有进位的加法运算
    carry = (a & b) << 1;//完成进位并且左移运算
    return add(sum, carry);
}
int main (void){
    int a = 8, b = 10;
    cout <<  add(a, b) << endl;
    return 0;
}
