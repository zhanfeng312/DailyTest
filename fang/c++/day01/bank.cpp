#include <iostream>
using namespace std;
void print(int money) {
    cout << money << endl;
}
//农行名字空间
namespace abc {
    int balance = 0;
    void save(int money) {
        balance += money;
    }
    void draw(int money) {
        balance -=money;
    }
    void salary(int money){
        balance += money;
    }
    void print(int money) {
        cout << "农行:";
        ::print(money);
    }
}
//建行名字空间
namespace ccb {
    int balance = 0;
    void save(int money) {
        balance += money;
    }
    void draw(int money) {
        balance -=money;
    }
    void salary(int money) {
        balance += money;
    }

}

int main(void) {
    using namespace abc;
    save(5000);
    cout << "农行:" << balance << endl;
    draw(3000);
    cout << "农行:" << balance << endl;
    // using namespace ccb;    //如果再加，编译器不知道那个名字空间,确实可以简化程序
    ccb::save(8000);
    cout << "建行:" << ccb::balance << endl;
    ccb::draw(5000);
    cout << "建行:" << ccb::balance << endl;
    using ccb::salary;  //名字空间声明
    salary(6000);
    cout << "建行:" << ccb::balance << endl;
    cout << 
    return 0;
}


