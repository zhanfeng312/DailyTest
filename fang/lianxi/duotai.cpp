#include <iostream>
#include <cstdio>
using namespace std;
class A {
    public:
        virtual void fun(){
            printf("virtual A::fun()\n");
        }
};
class B : public /*virtual*/ A{
    public:
        virtual void foo(){
            printf("B::foo()\n");
        }
};
int main (void){
    cout << sizeof (A) << endl; //4
    cout << sizeof (B) << endl; //
    /*int a = 1;
    cout << sizeof (int) << endl;
    cout << sizeof a << endl;
    */
    return 0;
}
