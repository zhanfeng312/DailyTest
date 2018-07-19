#include <iostream>
#include <cstdio>
#include <csetjmp> //实现远跳
using namespace std;
jmp_buf g_env;   //定义一个缓冲区
class A {
public:
    A (void) {
        cout << "构造" << endl;
    }
    ~A (void) {
        cout << "析构" << endl;
    }
};
void fun3 (void) {
    A a;
    FILE* fp = fopen ("none", "r"); 
    if (! fp)  //如果打开失败
        longjmp (g_env, -1);  //为C程序员量身定做的，C里面没有
    //...
    fclose (fp);
}
void fun2 (void) {
    A a;
    fun3 ();
}
void fun1 (void) {
    A a;
    fun2();
    //...
}
int main (void) {
    if (setjmp (g_env) == -1) {   //setjmp函数返回两次,第一次返回0，第二次返回-1
        cout << "没有那个文件" << endl;
        return -1;
    }
        fun1();
    cout << "执行成功，恭喜恭喜" << endl;
    return 0;
}

