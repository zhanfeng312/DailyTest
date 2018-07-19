#include <iostream>
#include <vector>
using namespace std;
void print(const vector<int>& vi){
    size_t size = vi.size();
    cout << size << endl;
    for (size_t i = 0; i < size; ++i)
        cout << vi[i] << ' ';
    cout << endl;
}
int main(void){
    vector<int> vi;
    vi.push_back (10);
    vi.push_back (20);
    vi.push_back (30);
    vi.push_back (40);
    vi.push_back (50);
    print(vi);
    vi.pop_back();
    print(vi);
    ++vi.front();
    vi.back() = 100;
    print(vi);
    typedef vector<int>::iterator IT;
    typedef vector<int>::const_iterator CIT;
    typedef vector<int>::reverse_iterator RIT;
    typedef vector<int>::const_reverse_iterator CRIT;
    for (IT it = vi.begin(); it != vi.end(); it++){
        ++*it;
    }
    const vector<int>& cvi = vi;
    for (CIT it = cvi.begin(); it != cvi.end(); ++it)
        cout << *it << ' ';//迭代器也是常量型的
    cout << endl;
    for (RIT it = vi.rbegin(); it != vi.rend(); it++)
        cout << *it << ' ';
    cout << endl;
    return 0;
}
