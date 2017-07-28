#include <iostream>
using namespace std;
class A {
    virtual void foo (void) {}
};
class B : public A {};
class C : public B {};
class D {};
int main(void){
    B b;
    A* pa = &b;
    cout << pa << endl;
    cout << "------------dc------------" << endl;
    //pa指向B对象,成功
    B* pb = dynamic_cast<B*> (pa);
    cout << pb << endl;
    //pa没有指向C对象，失败，安全
    C* pc = dynamic_cast<C*> (pa);
    cout << pc << endl;
    A& ra = b;
    try {
        C& rc = dynamic_cast<C&> (ra);
    }
    catch (exception& ex) {
        cout << "类型转换失败:" << ex.what()
            << endl;
        //.....
    }
    //pa没有指向D对象，失败，安全
    D* pd = dynamic_cast<D*> (pa);
    cout << pd <<endl;
    cout << "------------sc------------" << endl;
    //B是A的子类，成功
    pb = static_cast<B*>(pa);
    cout << pb << endl;
    //C是A的孙子类，成功，危险！
    pc = static_cast<C*>(pa);
    cout << pc << endl;
    //D不是A的后裔
    //pd = static_cast<D*> (pa);
    //cout << pd << endl;
    cout << "-------------------------rc-------" << endl;
    //无论在编译期还是在运行期都不做检查，危险！
    pb = reinterpret_cast<B*>(pa);
    cout << pb << endl;
    pc = reinterpret_cast<C*>(pa);
    cout << pc << endl;
    pd = reinterpret_cast<D*> (pa);
    cout << pd << endl;
    return 0;
}
