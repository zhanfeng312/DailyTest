#include <iostream>

using namespace std;
class Complex{
public:
    Complex(int r = 0,int i = 0):
        m_r(r), m_i(i) {}
    void print(void) const {
        cout << m_r << '+' << m_i << 'i' << endl;
    }
    Complex& operator++ (void) {
        ++m_r;
        ++m_i;
        return *this;  //为了返回左值
    }
    friend Complex& operator--(Complex& o) {
        --o.m_r;
        --o.m_i;
        return o;
    }
private:
    int m_r;
    int m_i;
};
int main(void) {
    Complex c1 (1, 2);
    Complex c2 = ++c1; //c2 = c1.operator++()
    c1.print();  //2+3i
    c2.print();  //2+3i
    (++c1) = Complex (10, 20);
    c1.print();  //10 + 20i
    (++++++c1).print(); //13+23i
    c2 = --c1;  //c2 =::operator--(c1);全
    c1.print(); //12+22i
    c2.print(); //12+22i
    return 0;
}
