#include <iostream>
using namespace std;
class A{
public:
    A(int a, int b) : m_a(a), m_b(b){}
    int get() const{
        return m_a;
    }
    void func(){
        m_b = 5;
    }
private:
    int m_a;
    const int m_b;
};
int main (void){
    A a(2, 3);
    a.func();
    cout << a.get();
    return 0;
}
