#include <iostream>
using namespace std;
void func(const int* p) //不能通过*p改变指针p的目标值
{
    *p =+ 1;
}
int main (){
    int a = 58;
    func(&a);
    cout << a << endl;
    return 0;
}
