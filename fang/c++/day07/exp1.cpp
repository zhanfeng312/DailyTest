#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
void foo(void) {
    FILE* fp = fopen ("none", "r");
    if (! fp)
        throw "打开文件失败!"; //抛出基本类型
    void* pv = malloc (0xFFFFFFFF); //分配很大内存
    throw -1;
    if (! pv)
        throw "内存分配失败!";
   //...
}
int main(void) {
    try {
        //可能抛出异常的语句块
        foo();
        cout << "123" << endl;
    }
    catch (const char* ex) {
        cout << ex << endl;
        return -1;
    }
    catch (...){
        cout << "fang" << endl;
        return -1;
    }
    return 0;
}
