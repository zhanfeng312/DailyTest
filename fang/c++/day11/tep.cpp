#include <iostream>
#include <typeinfo>
#include <cstring>
using namespace std;
//函数模板/模板函数
template<typename T> //类型形参
T Max (T x, T y) {
    cout << typeid(T).name() << endl;
    return x > y ? x : y;
}
template<>
char* Max (char* x, char* y) {
    return strcmp(x, y) > 0 ? x : y;
}
template<typename T>
void foo (void) {
    T t;
    cout << typeid(t).name() << endl;
}

int main (void) {
    /*cout << "请输入:" << endl;
    string s1, s2;
    cin >> s1 >> s2;
    cout << "最大值为:" << Max<string>(s1, s2) << endl; //后面的尖括号可以不写,可以推断
    */
    char cx[256], cy[256];
    cin >> cx >> cy;
    cout << "最大值" << Max (cx, cy) << endl;
    foo<int>();
    return 0;
}
