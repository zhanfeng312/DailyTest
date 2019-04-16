#include <iostream>
using namespace std;
int f(unsigned long a){
    if (0 == a)
        return 1;
    else
        return a * f(a-1);
}
int main (void){
    unsigned long a;
    cin >> a;
    cout << f(a) << endl;
    return 0;
}
