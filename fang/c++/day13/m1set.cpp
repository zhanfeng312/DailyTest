#include <iostream>
#include <set>
using namespace std;
int main (void) {
    const char* candidate[] = {
        "张飞", "赵云", "关羽", "刘备", "曹操", NULL};
    multiset<string> ms;
    for (size_t i= 0; i < 10; ++i) {
        for (size_t i = 0; candidate[i];++i)
            cout << '(' << char ('A' + i) << ')'
                << candidate[i] << ' ';
        cout << endl << "请投下您庄严的一票" << flush;
        char key;
        cin >> key;
        if (key < 'A' || 'E' < key) {
            cout << "此票无效！" << endl;
            continue;
        }
        ms.insert (candidate[key - 'A']);
    }
    multiset<string>::iterator win = ms.begin ();
    for (multiset<string>::iterator it = ms.begin ();
            it != ms.end (); ++it){
        cout << *it << "获得" << ms.count (*it)
            << "票。" << endl;
        if (ms.count (*it) > ms.count (*win))
            win = it;
        it = ms.upper_bound (*it);
        --it;
    }
    cout << "热烈祝贺" << *win << "当选" << endl;

    return 0;
}
