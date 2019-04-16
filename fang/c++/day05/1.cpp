#include <iostream>
using namespace std;
int main(void) {
    int i =0;
    (++i) = 100;
    cout << i << endl;  //100
    cout << ++++++i << endl;//103
    return 0;
}
