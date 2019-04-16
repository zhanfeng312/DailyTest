#include <iostream>
#include <queue>
#include <list>
using namespace std;
int main (void) {
    queue<string, list<string> > qs; //队列容器,底层容器为列表
    qs.push ("我");
    qs.push ("要");
    qs.push ("吃");
    qs.push ("饭");
    while (! qs.empty()) {
        cout << qs.front ();
        qs.pop ();
    }
    cout << endl;

    return 0;
}
