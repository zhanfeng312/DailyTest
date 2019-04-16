#include <iostream>
using namespace std;
class A{
public :
    A (void) {
        cout << "构造: " << this << endl; //构造函数中,this指正在被构造的对象
    }
    void foo(void) {
        cout << "foo: " << this << endl;  //成员函数中,this指向调用该函数的对象
    }
};
int main(void){
    A a;
    cout << "main: " << &a << endl;
    a.foo(); 
    A* pa = new A;
    cout << "main: " << pa << endl;
    pa->foo();
    return 0;
}
