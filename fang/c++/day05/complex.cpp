#include <iostream>
using namespace std;
class Complex{
    public:
        Complex(int r = 0, int i = 0):
            m_r(r), m_i(i){}
        //打印信息
        void print() const{
            cout << m_r << "+"<<m_i <<"i"<<endl;
        }
        //不加最后const,表示this指针是Complex*类型的,左操作数为常对象
        //非常指针指向常对象
        //第一个const: 返回右值; 
        //第二个const: 支持常量型右操作数;
        //第三个const: 支持常量型的左操作数
        /*********重载+操作符******************/
        const Complex operator+ (const Complex& c2) const{
            return Complex(m_r + c2.m_r, m_i + c2.m_i);
        }
        /*******<<操作符重载,这样就可以输出*********/
        friend ostream& operator<< (ostream& os, const Complex& c){
            return os << c.m_r << "+"<< c.m_i<<"i";
        }
        /*****+=操作符重载,证明返回左操作数的引用****/
        Complex& operator+= (const Complex& c2){
            m_r = m_r + c2.m_r;
            m_i = m_i + c2.m_i;
            return *this;
        }
        /******重载前++操作符*******/
        Complex& operator++(void){
            ++m_r;
            ++m_i;
            return *this;
        }
    private:
        int m_r;
        int m_i;
        //友元声明
        friend const Complex operator- (const Complex&, 
           const Complex&);
};
    const Complex operator- (const Complex& l, 
        const Complex& r){
        return Complex(l.m_r - r.m_r, l.m_i - r.m_i);
    }
int main(void){
    const Complex c1 (1, 2);
    c1.print();
    const Complex c2 (2, 4);
    Complex c3 = c1 + c2;//c1.operator + (c2);
    c3.print();
    c3 = c2 - c1;//c3 = ::operator-(c2, c1);
    c3.print();
    cout << c3 << c2 << endl;
    c3 += c1;
    cout << c3 << endl;
    ++c3;
    cout << c3 << endl;
    return 0;
}
