#include <iostream>
#include <memory>
using namespace std;
class A{
public:
    A(void) {
        cout << "构造" << endl;
    }
    ~A(void) {
        cout << "析构" << endl;
    }
    void hello(void) {
        cout << "Hello World" << endl;
    }
};
class PA{
public:
    PA (A* p = NULL) : m_p(p) {}
    ~PA (void) {
        if(m_p) {
            delete m_p;
            m_p = NULL;
        }
    }
    A& operator* (void) const {
        return *m_p;
    }
    A* operator-> (void) const {
        //return &**this;
        return m_p;
    }
    PA (PA& that) : m_p(that.release()) {}
    PA& operator= (PA& that) {
        if(&that != this) 
            reset (that.release());
        return *this;
    }
private:
    A* release (void) {
        A* p = m_p; //备份了一下
        m_p = NULL;
        return p;
    }
    void reset(A* p) {
        if(p != m_p) {
            delete m_p;
            m_p = p;
        }
    }
    A* m_p;
};
void bar (auto_ptr<A> pa) {
    cout << "bar:" ;
    pa -> hello();
}
void foo(void) {
    PA pa (new A);
    //delete pa;
    //pa ->hello();
    //(*pa).hello();
    //A* pb = pa;
    pa -> hello(); //pa.operator->()->hello();
    (*pa).hello();//把类类型的对象当成指针来使用pa.operator*().hello();
    PA pb = pa;
    pb ->hello();
    auto_ptr<A> pa1 (new A); //指向啥类型的对象
    pa1 -> hello();
    auto_ptr<A> pa2 = pa1;
    pa2 -> hello();
    bar (pa2);  //值传递,传完后pa2为空
    cout << pa2.get() << endl;
}
//smart_ptr
int main(void) {
    foo();
    return 0;
}

