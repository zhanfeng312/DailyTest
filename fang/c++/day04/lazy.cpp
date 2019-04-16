#include <iostream>
using namespace std;
class Singleton{
public:
    static Singleton& getInst(void) {
        if(! m_inst)
            m_inst = new Singleton;
        ++m_ch;
        return *m_inst;
    }
    void releaseInst (void) {
        if(m_ch && --m_ch == 0)
            delete this;
    }
private:
    Singleton (void) {
        cout << "构造" << this << endl;
    }
    Singleton (const Singleton&);
    ~Singleton (void) {
        cout << "析构" << this << endl;
        m_inst = NULL;
    }
    static Singleton* m_inst;  //静态成员变量
    static unsigned int m_ch;
};
Singleton* Singleton::m_inst = NULL; //定义并初始化
unsigned int Singleton::m_ch = 0;
int main(void) {
    Singleton& s1 = Singleton::getInst();
    Singleton& s2 = Singleton::getInst();
    Singleton& s3 = Singleton::getInst();
    cout << &s1 << ' ' << &s2 << ' ' << &s3 << endl;

    s3.releaseInst();
    s2.releaseInst();
    s3.releaseInst();

    return 0;
}
