#include <iostream>
using namespace std;
class Integer{
public:
    Integer (int data = 0) : m_data(data) {}
    void print(void) const {
        cout << m_data << endl;
    }
    
     /*Integer (const Integer& that) : //编译器,虚实结合时，也会调用复制构造函数
     m_data(that.m_data){
         cout << "拷贝构造" << endl;
     }*/
    
    Integer(const Integer& that) :   //Integer类型的常引用
        m_data(that.m_data){
            cout << "拷贝构造" << endl;
        }
private:
    int m_data;
};
void foo(Integer i){
    i.print();
}

Integer bar(void) {
    Integer i;   //bar函数栈
    return i;     //函数返回时,i的值已经被释放
}
int main(void) {
    Integer i1(10);
    Integer i2(i1);  //拷贝构造

    i1.print();
    i2.print();
    Integer i3 = i1; //拷贝构造,初始化
    i3.print();
    
    //Integer i4(10, 20);
    
    cout << "调用foo()函数" << endl;
    foo(i1);
    cout << "调用bar()函数" << endl;
    Integer i4 = bar(); //所以不会调用拷贝构造函数

    return 0;
}

