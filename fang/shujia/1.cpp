#include <iostream>
#include <stdlib.h>
using namespace std;
int func (int n){
    if (n <= 0){
        cout << "error"<< endl;
        exit(1);
    }
    else if (n == 1)
        return 1;
    else if (n % 2 == 0)
        return -n + func (n-1);
    else
        return n + func(n-1);
}
int main (void){
    cout << "n = "; 
    int n;
    cin >> n;
    int res = func(n);
    if (res)
        cout << "结果为:" << res << endl;
    return 0;
}
