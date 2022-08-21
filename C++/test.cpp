#include <iostream>

using namespace std;

class Base {
    public:
        //函数重载, 函数名相同，参数不同
        void func(void) {
            cout << "Base::func(void)" << endl;
        }

        void func(int a) {
            cout << "Base::func(int) " << a << endl;
        }

        virtual void test(void) {
            cout << "Base::test" << endl;
        }
};

/* 公有继承 */
class Derive : public Base {
    public:
        //隐藏: 子类和父类有函数名字相同的函数
        void func(void) {
            cout << "Derive::void" << endl;
        }

        //重写(覆盖) 子类和父类的test函数完全相同, 基类中被重写的函数必须有virtual关键字
        void test(void) {
            cout << "Derive::test" << endl;
        }
};

int main(void)
{
    Derive pd;
    pd.func(); //Derive::void
    //pd.func(1); //error, func函数被隐藏，只能调用func()函数

    Base *base = &pd; //指向子类对象的基类指针
    base->func(1); //Base::int 1
    base->func();  //Base::void

    base->test(); //Derive::test

    return 0;
}