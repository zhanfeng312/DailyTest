#include <iostream>
using namespace std;
class Counter{
public :
    Counter(void) : m_data(0) {}
    Counter& inc(void) {
        ++m_data;
        return *this;  //this指向当前的类对象
    }
    void print(void) {
        cout << m_data << endl;
    }
private :
    int m_data;
};
int main(void) {
    Counter c;
    //c.inc();
    //c.inc();
    //c.inc(); 可以这样写
    c.inc().inc().inc();
    c.print();

    return 0;

}
