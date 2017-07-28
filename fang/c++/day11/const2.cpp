#include <iostream>
using namespace std;
template<typename T>
class A {
public:
    A (const T& t) : m_t (t) {}
    /*
    template<typename Y>
    void print (const Y & y) {
        cout << m_t << ' ' << y << endl;
    }
    */
    template<typename Y>
    void print (const Y& y);
    T m_t;
};
template<typename T>
  template<typename Y>
void A<T>::print (const Y& y) {
      cout << m_t << ' ' << y << endl;
}
int main(void) {
    A<int> a (100);
    a.print<string> ("Hello");
    return 0;
}
