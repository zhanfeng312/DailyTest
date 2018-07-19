#include <iostream>
using namespace std;
class A {
public:
    virtual void foo (void) {
        cout << "A::bar()" << endl;
    }
    virtual void bar (void) {
        cout << "B::bar()" << endl;
    }
};
class B : public A {
public:
    void foo (void) {
        cout << "B::foo()" << endl;
    }
};
int main (void) {
    A a;
    void (**vft) (void) = *(void (***) (void))&a;
    cout << (void*)vft[0] << ' ' <<(void*)vft[1] << endl;
    vft[0] ();
    vft[1] ();
    B b;
    vft = *(void (***) (void))&b;
    cout << (void*)vft[0] << ' '
        << (void*)vft[1] << endl;
    vft[0] ();
    vft[1] ();
    return 0;
}
