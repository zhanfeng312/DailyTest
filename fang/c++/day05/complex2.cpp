#include <iostream>
using namespace std;
class Complex{
public:
    Complex(int r = 0, int i = 0):
        m_r(r), m_i(i) {}
    void print(void) const {
        cout << m_r << '+' << m_i << 'i' << endl;
    }
    Complex& operator += (const Complex& r) {
        m_r += r.m_r;
        m_i += r.m_i;
        return *this;
    }
    friend ostream& operator <<(ostream& os,const Complex& r) {
       return  os << r.m_r << '+' << r.m_i << 'i';
    }
    friend istream& operator >> (istream& is, Complex& r) {
        return is >> r.m_r >> r.m_i;
    }
private:
    int m_r;
    int m_i;
};
int main(void) {
    Complex c1 (1, 2), c2(3, 4);
    cout << c1 << endl << c2 << endl;
    //::operator<< (::operator<<(cout, c1).operator<<(endl).c2).operator<<(endl);
    return 0;
}
