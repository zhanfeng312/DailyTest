#include <iostream>
using namespace std;
int g_data = 100;
int& foo(void)    //引用型返回值
{
    return g_data;
}
/*int& bar(void)
{
    int a = 100;
    return a;
}
int& fun(void)
{
    int b = 200;
    return b;
}*/
int& hum(int& a)
{
    return a;
}
int main(void){
    int data = foo();
    cout << data << endl;  //100
    foo() = 200;
    cout << g_data << endl;
    /*
    foo() += 100;
    ++foo();
    cout << g_data << endl;  //301
    int& a = bar();
    //fun();
    cout << a << endl;*/
   return 0;
}
