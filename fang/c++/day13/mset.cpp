#include <iostream>
#include <map>
using namespace std;
int main (void) {
    multimap<string, int> msi;
    msi.insert (make_pair ("张飞", 100000));
    msi.insert (make_pair ("赵云", 200000));
    msi.insert (make_pair ("张飞", 300000));
    msi.insert (make_pair ("关羽", 400000));
    msi.insert (make_pair ("赵云", 500000));
    msi.insert (make_pair ("关羽", 600000));
    typedef multimap<string, int>::const_iterator CIT;
    for (CIT it = msi.begin(); it != msi.end();++it)
        cout << it->first << ":" << it->second << endl;
    for (CIT it = msi.begin(); it != msi.end();++it){
        string key = it->first;
        CIT end = msi.upper_bound (key);
        int sum = 0;
        for (; it != end; ++it)
            sum += it->second;
        cout << key << " : " << sum << endl;
        --it;
    }
    return 0;
}
