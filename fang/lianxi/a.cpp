#include <iostream>
using namespace std;
int main(void){
    int a = 1;
    (++a) += (a++);
    cout << a << endl; 
    int i = 2;
    (++i) = 3;
    cout << i << endl;
    return 0;
}
