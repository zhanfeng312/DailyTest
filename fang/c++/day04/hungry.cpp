#include <iostream>
using namespace std;
//饿汉方式
class Singleton{
public:
    static Singleton& getInst(void) {
        return s_inst;
    }
private:
    Singleton (void){}
    Singleton (const Singleton&);
    static Singleton s_inst;
};
Singleton Singleton::s_inst;
int main(void){
    Singleton& s1 = Singleton::getInst();;
    Singleton& s2 = Singleton::getInst();;
    Singleton& s3 = Singleton::getInst();;
    return 0;
}

