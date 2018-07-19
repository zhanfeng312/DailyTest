#include<iostream>
using namespace std;
void foo(int a){
    cout << "foo(int)" << endl;
}
void bar(int a){}
//int foo(int a){}
int foo(int a, double b){
    cout << "foo(int,double)" << endl;
}
int foo(double a,int b){
    cout << "foo(double,int)" << endl; 
}
// 对应比较
//int foo(int b, double a){} //看类型，对第六行重定义
int main(void){
    foo(100);
    foo(100, 1.23);
    foo(1.23, 100);
    //foo(100, 100);   歧义, 不匹配
    return 0;
}
