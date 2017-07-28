#include <iostream>
#include <vector>
using namespace std;
class A{
    public:
        A(int i = 0):m_i (i){};
        int m_i;
};
void print (const vector<int>& vi) {
    size_t size = vi.size ();
    cout << size << endl;
   for (size_t i = 0; i < size; ++i)
        cout << vi[i] << ' ';
    cout << endl;
}
int main (void) {
    /*vector<int> vi;
    vi.push_back (10);
    vi.push_back (20);
    vi.push_back (30);
    vi.push_back (20);
    vi.push_back (10);
    print (vi);
    i.pop_back ();
    print (vi);
    ++vi.front ();
    vi.back () = 100;
    cout << vi.front () << ' ' << vi.back () << endl;
    typedef vector<int>::iterator IT;
    typedef vector<int>::const_iterator CIT;
    typedef vector<int>::reverse_iterator RIT;
    typedef vector<int>::const_reverse_iterator CRIT;
    for (IT it = vi.begin (); it != vi.end ();it++)
        ++*it;
    const vector<int>& cvi = vi;
    for (CIT it = cvi.begin (); it != cvi.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    for (CRIT it = cvi.rbegin (); it != cvi.rend(); ++it)
        cout << *it << ' ';
    cout << endl;
    */
    vector<string> vs;
    vs.push_back ("beijing");
    vs.push_back ("tianjin");
    vs.push_back ("shanghai");
    cout << *(vs.begin () + 2) << endl;
    *const_cast<char*> ((vs.end () - 1) ->c_str ()) = 'S';//常类型转换
    cout << *(vs.end () - 1) << endl;
    vector<int> vi2 (10, 8);
    print (vi2);
    vector<A> va1(10);
    for (vector<A>::const_iterator it = va1.begin();
            it != va1.end(); ++it)  //有缺省的参数,当没写参数时,就用缺省的用
        cout << it->m_i << ' ';
    cout << endl;
    vector<A> va2(10, A(8));
    for (vector<A>::const_iterator it = va2.begin();
            it != va2.end(); ++it)
        cout << it->m_i << ' ';
    cout << endl;
    return 0;
}
