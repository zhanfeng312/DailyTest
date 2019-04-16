#include <iostream>
#include <cstdlib>
using namespace std;
class A {
public:
    ~A(void) {}
    static void* operator new (size_t size) { //size_t 是类型别名,unsigned int
        void* p = malloc (size);
        cout << "我的new:" << p << ' '
            << size <<endl;
        return p;
    }
    static void operator delete (void* p) {
        cout << "我的delete:" << p << endl;
        free(p);
    }
    static void* operator new[] (size_t size) {
        void* p = malloc(size);
        cout << "我的new[] :" << p << ' '
            << size << endl;
        return p;
    }
    static void operator delete[] (void* p){
        cout << "我的delete[]:" << p << endl;
        free(p);
    }
private:
    int m_i;
    double m_d;
    char m_c;
};
int main(void) {
    cout << sizeof(A) << endl;
    A* pa = new A;
    cout << pa << endl;
    delete pa;
    pa = new A[2];
    cout << pa << endl;
    delete[] pa;
    return 0;
}

