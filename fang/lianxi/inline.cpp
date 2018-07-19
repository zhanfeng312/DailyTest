#include <iostream>
using namespace std;
class A {
public:
    int add (int a, int b);
};
inline int A::add (int a, int b){
    return a + b;
}
int main (void){
    A a;
    cout << a.add(3, 5) << endl;
    return 0;
}
