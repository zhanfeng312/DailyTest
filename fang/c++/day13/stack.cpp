#include <stack>
#include <iostream>
#include <list>
using namespace std;
int main (void) {
    stack<string, list<string> > ss; //底层容器vector
    ss.push ("吃饭");
    ss.push ("喜欢");
    ss.push ("我");
    while (! ss.empty ()){  //当栈不为空时
        cout << ss.top();
        ss.pop();
    }
    cout << endl;
    return 0;
}
