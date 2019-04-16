#include <iostream>
using namespace std;
int main(){
    int a = 100,c = 200;
    int& b = a; //b是a的一个别名,改变b其实就是该a
    b = c;
    cout << a << endl;

    return 0;
}

