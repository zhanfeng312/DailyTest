#include <iostream>
using namespace std;
class A{ 
public:
    static int m_i;  //静态成员变量为多个对象所共享，只有一份实例
    static void foo(void){ 
        //静态成员函数。这样的函数没有this指针,无法访问非静态成员.
        cout << "foo:" << m_i << endl;
        //m_d = 3.14;
        bar();
    }
    double m_d;
    static void bar(void){
       m_i = 1000;
       foo();
    }
};
int A::m_i = 1;  //必须在类外定义并初始化
int main(void) {
    A::m_i = 10;
    A a1, a2;
    cout << ++a1.m_i << endl; //11
    cout << a2.m_i << endl;   //11
    A::foo();
    a1.foo();
    a1.bar();
    return 0;
}
