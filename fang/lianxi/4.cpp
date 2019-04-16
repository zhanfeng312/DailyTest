#include <iostream>
using namespace std;
class A{
public:
    int get() const{
        return m_a;
    }
    friend class B;
private:
    int m_a;
};
class B{
    public:
        void Set(int i);
    private:
        A a;
};
void B::Set(int i)
{
    a.m_a = 1;
}
int main (void){
    B b;
    return 0;
}
