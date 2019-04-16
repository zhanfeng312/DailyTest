#ifndef _PRINT_H
#define _PRINT_H
#include <iostream>
using namespace std;
template<typename IT> //模板
void print (IT begin, IT end) {
    while (begin != end)
        cout << *begin++ << ' ';
    cout << endl;
}
#endif  //_PRINT_H
