#include <iostream>
using namespace std;
int main(void){
#ifdef __cplusplus
    int a = 5;
    cout << __LINE__ << endl;
    cout << __cplusplus << endl;
#endif
    return 0;
}
