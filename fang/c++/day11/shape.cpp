#include <iostream>
using namespace std;
template<typename BASE> 
class Shape : public BASE {
public:
    void draw (void) const {
        BASE::draw ();
    }
};
class Rect {
public:
    void draw (void) const {
        cout << "绘制矩形..." << endl;
    }
};
class Circle {
public:
    void draw (void) const {
        cout << "绘制圆形..." << endl;
    }
};
int main(void) {
    Shape<Rect> shape1;
    shape1.draw();
    Shape<Circle> shape2;
    shape2.draw();
    return 0;
}
