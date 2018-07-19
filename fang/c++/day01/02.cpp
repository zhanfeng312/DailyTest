#include <iostream>
using namespace std;
namespace ns1 {
    int foo(int a) {
        cout << "foo(int)" << endl;
        return a;
    }
};
namespace ns2 {
    double foo (double a) {
        cout << "foo(double)" << endl;
        return a;
    }
};
int main(void) {
    using namespace ns1;
    using namespace ns2;
    cout << foo(10) << endl;
    cout << foo(1.23) << endl;
    using ns1::foo;
    cout << foo(10) << endl;
    cout << foo(1.23) << endl;
    return 0;
}
