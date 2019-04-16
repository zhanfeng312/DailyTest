#include <iostream>
using namespace std;
class Complex{
public:
    Complex(int r = 0, int i = 0):
        m_r(r), m_i(i) {}
    void print(void) const {
        cout << m_r << "+" << m_i << "i" << endl;
    }
    Complex& operator += (const Complex& r) {  //操作符重载
        m_r += r.m_r;
        m_i += r.m_i;
        return *this;
    }
private:
    int m_r;
    int m_i;
};
int main(void) {
    Complex c1 (1, 2), c2(3, 4);
    c1 += c2;
    c1.print();  //4 + 6i 非常对象可以调用常函数
    Complex c3(5, 6);
    (c1 += c2) = c3;
    c1.print();  //5 + 6i
    return 0;
}
