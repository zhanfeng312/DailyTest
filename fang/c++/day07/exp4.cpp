#include <iostream>
using namespace std;
void foo(void){
    throw 10;
}
void bar (void) {
    try{
        foo();
    }
    catch (int& ex){ 
        --ex;
        throw;//继续抛出
    }
    catch (int& ex){
        ++ex;
        throw;
    }
    //...
}
int main (void) {
    try{
        bar();
    }
    catch (int& ex){
        cout << ex << endl; //9
    }
    return 0;
}
