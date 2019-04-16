#include <iostream>
using namespace std;
void foo(int a = 10, double b = 1.0 , const char*c = "tarena") { //=只是一种记法，不是赋值    
    cout << a << ' ' << b << ' ' << c << endl;
}
int main(){
    foo(1, 1.34, "Hello");
    foo(1, 1.34);
    foo(1);
    foo();
    return 0;
}
