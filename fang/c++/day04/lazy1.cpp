#include <iostream>
using namespace std;
class Single{
public:
    static Single& getSingle(){
        if (!single)
            single = new Single;
        return *single;
    }
private:
    Single(void){
        cout << "构造函数" << endl;
    }
    static Single* single;
};
Single* Single::single = NULL;
int main (void){
    Single& s1 = Single::getSingle();
    Single& s2 = Single::getSingle();
    cout << &s1 << ":" << &s2 << endl;
    return 0;
}
