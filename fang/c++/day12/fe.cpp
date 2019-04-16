#include <iostream>
//#include <algorithm>
using namespace std;
template<typename IT, typename DOIT>
void for_each(IT begin, IT end, DOIT doit){
    while(begin != end)
        doit(*begin++);
}
void print(int &x) {
    cout << x << endl;
}
void add(int& x){
    ++x;
}
int main (void){
    int a[5] = {1, 2, 3, 4, 5};
    for_each(a, a + 5, print);
    for_each(a, a + 5, add);
    for_each(a, a + 5, print);
    return 0;
}
