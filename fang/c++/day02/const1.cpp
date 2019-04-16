#include <iostream>
using namespace std;
int main(void) {
    int a = 100;
    const int* p1 = &a; //不能通过*p1该a的值，但可以直接通过a来改
    //*p1 = 200;
    a = 20;

    return 0;
}
