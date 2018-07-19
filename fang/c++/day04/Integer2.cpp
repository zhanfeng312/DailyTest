#include <iostream>
using namespace std;
class Integer {
public:
    Integer (int data) : m_data(new int(data)) {}
    ~Integer(void) {
        if(m_data){
            delete m_data;
            m_data = NULL;
        }
    }
    void print(void) const {
        cout << *m_data << endl;
    }
    /*
     Integer(const Integer& that):     //默认的拷贝构造函数
        m_data(that.m_data) {}
     */
    Integer (Integer& that) :    //不能用值来传参的原因
       m_data(new int (*that.m_data)) {}
    void set(int data) {
        *m_data = data;
    }
     Integer& operator = (const Integer& that) {
         //防止自赋值
         if (&that != this){
             //释放旧资源
             delete m_data;
             //分配新资源
             m_data = new int(*that.m_data);
             //拷贝新数据
         }
         //返回自引用
        return *this;
     }
private:
    int* m_data;
};
int main(void) {
    Integer i1(10);
    i1.print();
    Integer i2(i1);  //拷贝构造
    i2.set(20);
    i1.print();
    i2.print();
    Integer i3(30);
    i3.print(); //30
    i3 = i1;    //拷贝赋值
    //i3.operator = i1;
    i3.print(); //10
    i3.set(40);
    i3.print(); //40
    i1.print();
    (i3 = i1) = i2;
    i3.print();
    i3 = i3;
    i3.print();

    return 0;
}

