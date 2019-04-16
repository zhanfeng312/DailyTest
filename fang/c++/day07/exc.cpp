#include <iostream>
#include <cstdio>
using namespace std;
class A {
public:
    A (void) {
        cout << "A构造" << endl;
    }
    ~A (void) {
        cout << "A析构" << endl;
    }
};
void fun3 (void) {
    A a;
    FILE* fp = fopen ("none", "r"); 
    if (! fp) {      //如果打开失败
        cout << "throw前" << endl;
        throw -1;    //抛出异常
        cout << "throw后" << endl;
    }
    cout << "文件打开成功!" << endl;
    //...
    fclose (fp);
}
void fun2 (void) {
    A a;
    cout << "func3()前" << endl;
    fun3 ();
    cout << "func3()后" << endl;
}
void fun1 (void) {
    A a;
    cout << "func2()前" << endl;
    fun2();
    cout << "func2()后" << endl;
    //...
}
int main (void) {
    try {  //捕获异常并处理
        cout << "fun1()前" << endl;
        fun1();
        cout << "fun1()后" << endl;
    }
    catch (int ex) {
        if(ex == -1) {           
            cout << "没有那个文件" << endl;
            return -1;
        }
    }
    cout << "执行成功，恭喜恭喜" << endl;
    return 0;
}
