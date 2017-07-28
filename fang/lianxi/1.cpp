#include <iostream>
using namespace std;
class A {
    public:
        virtual void foo(void){
            cout << "A"<< endl;
        }
};
class B : public A {
    private:
        void foo(void){
            cout << "B" << endl;
        }
};
int main(void){
    B* b = new B;
    b->foo();
    return 0;
}
