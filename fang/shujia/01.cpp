#include <iostream>
using namespace std;
class A{
public:
    A(){
        cout << "constructor"<< endl;
    }
};
int main (void){
    A a;
    return 0;
}
