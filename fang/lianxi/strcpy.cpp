#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
int main (void){
    char str[20] = "0123456789";
    int a = strlen (str);
    int b = sizeof (str);
    cout << a << ":" << b << endl;
    /*char d[5] = "123";
    cout << sizeof (s) << endl;
    strcpy(d, s);
    for (size_t i = 0; i < 11;++i)
        cout << d[i] << ' ';
    cout << endl;
    printf("%s:%s\n", d, s);
    //cout << d << ":" << s << endl;
    */
    return 0;
}
