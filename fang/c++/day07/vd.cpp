#include <iostream>
using namespace std;
class A {
public:
    A (void) {
        cout << "A构造" << endl;
    }
    virtual ~A (void) {
        cout << "A析构" << endl;
    }
    
};
class B : public A {
public:
    B (void) {
        cout << "B构造" << endl;
    }
    ~B (void) {
        cout << "B析构" << endl;
    }
};
int main (void) {
    A* pa = new B;  //指向子类对象的基类指针,
                    //子类的析构函数会自动
                    //调用基类的析构函数
    delete pa;
    return 0;
}














