#include <iostream>
using namespace std;
int main(){
    /*
    int a = int (3.14);
    cout << a << endl;
    */
    int i = 0x12345678;
    cout << i << endl;
    char* p = reinterpret_cast<char*> (&i);
    for(size_t i = 0;i < 4;i++)
        cout << hex << (int)p[i] << ' ';
    cout << endl;
    
    float* q = reinterpret_cast<float*> (&i);
    cout << hex << *q << endl;
    
    void* v = reinterpret_cast<void*> (i);
    cout << v << endl;
    return 0;
}
