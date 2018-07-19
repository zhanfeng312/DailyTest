#include <iostream>
using namespace std;
void foo(const int& a)
{
    cout << a  << endl;
}
int main(void){
    char c = 'A';
    foo((int)c);

    return 0;
}
