#include <iostream>
using namespace std;
class A {
public:
    /*void bar(void){    //构成重载关系
        cout << "非常bar" << endl;
    }*/
    void bar(void) const{
        cout << "常bar" << endl;
    }
    //void XXXbarYY(A* this){}
    void foo(void) const{   //常函数
        //m_i = 100;
        const_cast<A*>(this)->m_i = 100;
    }
    //_ZNK1A3fooEv(const A* this){
    //   this->m_i = 100;
   // }
    /*mutable */int m_i;  //加上他以后，就变为const_cast<A*>(this)->m_i = 100;
};
int main(void){
    A a;
    a.foo();
    cout << a.m_i << endl;
    const A& r = a;
    //r.bar();
    a.bar();
    //XXXbarYYY(&r);   //const A*
    return 0;
}
