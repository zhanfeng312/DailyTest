#include <iostream>

using namespace std;
class Complex{
public:
    Complex(int r = 0,int i = 0):
        m_r(r), m_i(i) {}
    void print(void) const {
        cout << m_r << '+' << m_i << 'i' << endl;
    }
    const Complex operator++(int) {  //用哑元区分
        Complex old (*this);
        ++m_r;
        ++m_i;
        return old;
    }
    friend const Complex operator--(Complex& o,int) {
        Complex old(*this);
        --m_r;
        --m_i;
        return old;
    }

private:
    int m_r;
    int m_i;
};
int main(void) {
    Complex c1 (1, 2);
    Complex c2 = c1++; // c2 = c1.operator++(0)
    c1.print();   //2+3i
    c2.print();  //1+2i
    //(c1++) = c2;
    //c1++++++;
    c2 = c1--; //c2 = c1/operator(0)
    c1.print();
    c2.print();
    return 0;
}
