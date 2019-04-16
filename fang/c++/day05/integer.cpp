#include <iostream>
using namespace std;
class Square {
public:
    double operator() (double x) {
        return x * x;
    }
};

class Integer {
public:
    /*explicit*/ Integer (int i = 0) : m_i (i) {} //让它显示转换
    void print(void) const {
        cout << m_i << endl;
    }
    Integer& operator() (int i) { //函数操作符
        m_i += i;
        return *this;
    }
    Integer& operator,(int i) {
        m_i += i;
        return *this;
    }
    operator int (void) const {  //把Integer转换成int
        return m_i;
    }
private:
    int m_i;
};
void foo(const Integer& i) {
    i.print();
}
int main(void) {
    Square square;
    cout << square (3) << endl;
    //cout << square.operator() (3) << endl; //实际是这种情况。
    Integer i(10);
    i(1)(2)(3)(17); //33
    i.print();
    i, 1, 2, 3, 17;   //重载了，运算符
    i.print();  //56
    i = 100;   //通过单参构造实现自定义类型转换
    i.print();
    foo(200);
    int n = i;
    cout << n << endl;
    string str ("Hello Linux!");

    return 0;
}

