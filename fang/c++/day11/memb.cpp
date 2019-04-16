#include <iostream>
using namespace std;
template<typename T>
class A {
public:
    A (const T& t) : m_t (t) {}
    T m_t;
};
template<typename T, typename Y>
class B {
public:
    B (const T& t, const Y& y) :
        m_a (t), m_y (y){}
    A<T> m_a;
    Y m_y;
};
int main(void) {

    return 0;
}


