#include <iostream>
using namespace std;
int main(void) {
    enum E {a, b, c};
    E e;  //C++中枚举是一个独立的类型,直接用枚举常量来赋值
    e = a;
    e = b;
    e = c;
    //e = 1000;
    //e = 1;
    cout << e << endl;
    return 0;
}
