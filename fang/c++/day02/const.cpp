#include <iostream>
using namespace std;
int main(){
    //const /*volatile*/ int a = 100; //具有常属性的变量,不能通过它的标识符修改
    const volatile int a = 100;  //加volatile防止常量优化
    //a = 200;
    const volatile int* p1 = &a;
    //*p1 = 200;
    int* p2 = const_cast<int*> (p1); //给一个拥有const属性的指针去常
    *p2 = 200;
    cout << *p2 << endl;  //200
    cout << a << endl;    //200

    return 0;
}
