#include <iostream>
using namespace std;
void swap1(int a, int b)
{
    int c = a;
    a = b;
    b = c;
}
void swap2(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
void swap3(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}
void swap4(const char *x, const char *y)
{
    const char *z = x;
    x = y;
    y = z;
}
void swap5(const char** x, const char** y)
{
    const char*z = *x;
    *x = *y;
    *y = z;
}
void swap6(const char*& x, const char*& y)
{
    const char* z = x;
    x = y;
    y = z;
}
struct Student {
    char name[1024];
    int age;
};
void print(const struct Student& s)  //只读属性
{
    cout << s.name << ", " << s.age << endl;
   //s.age = -1;
e
void foo(const int& x)
{
    cout << x << endl;
}
int main(void) {
    int a = 100, b = 200;
    //swap1(a, b);
   // swap2(&a, &b);
    swap3(a, b);   //别名交换，实际实参也交换
    cout << a << ' ' << b << endl;
    const char * x = "hello",*y = "world";
    //swap4(x, y);
    //swap5(&x, &y);
    swap6(x, y);
    cout << x << ' ' << y << endl;
    Student s = {"张飞", 21};
    print(s);
    print(s);
    foo(100);
    return 0;
}
