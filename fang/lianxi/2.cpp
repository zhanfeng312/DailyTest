#include <iostream>
using namespace std;
class A {
};
int main (void){
    cout << sizeof (A) << endl;//sizeof(一个空的类),结果为1
cout <<__FILE__ << endl;
cout <<__LINE__ << endl;
    return 0;
}
