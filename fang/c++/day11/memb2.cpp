#include <iostream>
using namespace std;
template<typename T>
class A {
public:
    A (const T& t) : m_t (t) {}
    T m_t;
};
template<template<typename T> class Y>  //前一个模版做另一个模版的参数
class B {
public:
    B (const int& i, const string& s) :
        m_i (i), m_s (s) {}
    Y<int> m_i;
    Y<string> m_s;
};
int main(void) {
    B <A> b(100, "Hello");
    cout << b.m_i.m_t << ' ' << b.m_s.m_t << endl;
    return 0;
}


