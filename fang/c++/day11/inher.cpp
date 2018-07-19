#include <iostream>
using namespace std;
template<typename T>
class A {
public:
    A (const T& t) : m_t (t) {}
    T m_t;
};
template<typename T, typename Y>
class B : public A<T>{   //要在这块体现出来
public:
    B (const T& t, const Y& y) :
        A<T> (t),m_y (y) {}
    Y m_y;
};
int main(void) {
    B <int, string> b(100, "hello");
    cout << b.m_t << ' ' << b.m_y << endl;
    return 0;
}
