#include <iostream>
using namespace std;
class Double{
public :
    Double (double data) : m_data(new double (data)) {
        cout << "构造" << endl;
    }
    ~Double(void) {
        cout << "析构" << endl;
        delete m_data;
    }
    void print(void) const {
        cout << *m_data << endl;
    }
private:
    double* m_data;
};
int main(void) {
    Double d1(3.14);
    d1.print();
    Double* d2 = new Double(1.23);
    delete d2;   //在堆里面，是delete运算符调用析构函数，释放内存
    cout << "再见" << endl;
    return 0;
}

