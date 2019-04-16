#include <iostream>
using namespace std;
int main(void) {
    //匿名联合
    union {
        int x;
        char c[4];/*= {'A','B','C','D'};*/
    };
    cout << (void*)&x << ' ' <<  (void*)c << endl;
    x = 0x12345678;
    for(int i = 0;i < 4;i++)
        cout << hex << (int)c[i] << ' ';
    cout << endl;
    return 0;
}
