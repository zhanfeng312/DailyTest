#include <iostream>
#include <vector>
#include <algorithm>
#include "print.h"
using namespace std;
class A {
public:
    A (int i = 0):m_i(i) {
        cout << "无参构造:" << this << endl;
    }
    A (const A& that) : m_i (that.m_i) {
        cout << "拷贝构造:" << &that << "->"
            << this << endl;
    }
    A& operator = (const A& that) {
        cout << "拷贝赋值:" << &that << "->"
            << this << endl;
        if (&that != this)
            m_i = that.m_i;
        return *this;
    }
    ~A (void) {
        cout << "析构函数:" << this << endl;
    }
    operator int& (void){
        return m_i;
    }
    bool operator==(const A& that) const{
        return m_i == that.m_i;
    }
    //函数操作符,实例化的对象就可以被当作函数使用.
    bool operator() (const A& a, const A& b)const{
        return a.m_i < b.m_i;
    }
    /*
     bool operator < (const A& that) const{
        return m_i < that.m_i;
    }
    */
    /*operator const int& (void) const{
        return static_cast<int&>(
                const_cast<A&>(*this));
    }
    */
private:
    int m_i;
};
int main (void) {
    cout << "-------1-------" << endl;
    vector<A> va (3);  //将va初始化为3个A对象
    cout << "-------2--------"<< endl;
    va.push_back(A ());
    cout << "-------3--------"<< endl;
    va.erase(va.begin());
    cout << "-------0--------"<< endl;
    va[0] = A(10);
    va[1] = A(50);
    va[2] = A(70);
    va.push_back(A(60));
    
    vector<A>::iterator it = find(va.begin(),
            va.end(), A(90));
    if (it == va.end())
        cout << "没找到!" << endl;
    else
        cout << "找到了"<<*it << endl;
    //sort(va.begin(), va.end());
    /*
    sort(va.begin(), va.end(), va[0]);
    print(va.begin(), va.end());
    */
    return 0;
}
