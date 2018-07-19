#include <iostream>
using namespace std;
class Shape {    //抽象类，不能实例化对象
public:
    Shape (int x, int y) : m_x (x), m_y (y) {}
    virtual void draw (void) = 0;  //draw是纯虚函数
protected:
    int m_x, m_y;
};

int main(void) {
    //Shape shape(1, 2);  
    return 0;
}
