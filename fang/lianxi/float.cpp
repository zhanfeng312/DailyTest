#include <iostream>
using namespace std;
int main (void){
    double f = 1.8;
    int i = int(f);
    cout << i << endl;
    cout << (int&)f << endl;
    return 0;
}
