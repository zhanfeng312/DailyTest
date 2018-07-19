#include <iostream>
#include <cstdio>
using namespace std;
int fun3 (void) {
    FILE* fp = fopen ("none", "r");
    if (! fp)
        return -1;
    //...
    fclose (fp);
    return 0;
}
int fun2 (void) {
    if (fun3 () == -1)
        return -1;
    //...
    return 0;
}
int fun1 (void) {
    if (fun2 () == -1)
        return -1;
    //...
    return 0;
}
int main (void) {
    if (fun1 () == -1){
        cout << "执行失败！改天再见！" << endl;
        return -1;
    }
    cout << "执行成功，恭喜恭喜" << endl;
    return 0;
}

