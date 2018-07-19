#include <iostream>
using namespace std;
void foo(const int& a) {
    cout << a << endl;
}
int main(void) {
    char c = 'A';
    foo((int)c);   //临时变量都是右值,都带有常属性
    return 0;
}
