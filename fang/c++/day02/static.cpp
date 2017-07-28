#include <iostream>
using namespace std;
int main(){
    int* p1 = NULL;
    void* p2 = p1;
    p1 = static_cast<int*> (p2);
    p2 = (void*)p1;
    return 0;
}
