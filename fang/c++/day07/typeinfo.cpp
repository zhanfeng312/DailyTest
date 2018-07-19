#include <iostream>
#include <typeinfo>
using namespace std;
class A {
    virtual void foo(void){}
};
class B : public A {};
void print (A* pa){
    //if (typeid (*pa).name() == string ("1A"))
    if (typeid (*pa) == typeid (A))
        cout << "pa指向A对象!" << endl;
    else 
        //if (typeid (*pa).name() == string ("1B"))
    if(typeid (*pa) == typeid (B))
        cout << "pa指向B对象!" << endl;
}
int main(void) {
    cout << typeid (int).name () << endl;
    cout << typeid (unsigned int).name () << endl;
    cout << typeid (double[10]).name () << endl;
    cout << typeid (char[3][4][5]).name () << endl;
    char* (*p[5]) (int*, short*);  //函数指针数组
    cout << typeid(p).name() << endl;
    cout << typeid (const char* const* const).name()
        << endl;
    cout << typeid (A).name() << endl;
    A* pa = new B;
    cout << typeid (*pa).name() << endl; //有多态，指针指向目标对象
    print (new A);
    print (new B);
    return 0;
}
