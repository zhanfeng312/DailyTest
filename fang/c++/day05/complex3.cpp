#include <iostream>
using namespace std;
class Complex{
public:
    Complex(int r = 0,int i = 0):
        m_r(r), m_i(i) {}
    void print(void) const {
        cout << m_r << '+' << m_i << 'i' << endl;
    }
    Complex& operator += (const Complex& r) {
        m_r += r.m_r;
        m_i += r.m_i;
        return *this;
    }
   /* friend ostream& operator <<(ostream& os,const Complex& r) {
       return  os << r.m_r << '+' << r.m_i << 'i';
    }
    friend istream& operator >> (istream& is, Complex& r) {
        return is >> r.m_r >> r.m_i;
    }
    */
    const Complex operator-(void) const { //返回类型只能是右值，后面加const，表示常量型的操作数
        return Complex(-m_r, -m_i);
    }
    /*
    friend const Complex operator~ (const Complex& o){ //c1在计算前后不发生改变
        return Complex(o.m_i, o.m_r);
    }*/
    const Complex operator ~ (void) const {
        return Complex(m_i, m_r);
    }
private:
    int m_r;
    int m_i;
};
int main(void) {
    Complex c1 (1, 2);
    Complex c2 = -c1;// c2 = c1.operator-()
    c2.print();  //-1+-2i
    Complex c3 = ~c1;   //c3 = ::operator~(c1)全局形式要考虑友元函数
    c3.print();
    return 0;
}
