#include <iostream>
using namespace std;
void foo(int a = 10, double b = 0.01, const char *c = "tarena");
void foo(void){}
void bar(int){
    cout << "bar(int)" << endl;
}
void bar(int, double){
    cout << "bar(int, double)" << endl;
}
int main(void){
    foo(1, 3.14, "hello");
    foo(1, 3.14);
    foo(1);
    //foo(); 歧义
    bar(100);
    bar(100, 12.34);
    return 0;
}
//foo函数定义
void foo(int a/* = 10*/, double b/*= 0.01*/, const char *c/* = "tarena"*/){
    cout << a << ' ' << b << ' ' << c << endl;
}
