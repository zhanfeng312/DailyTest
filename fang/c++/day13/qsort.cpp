#include <iostream>
#include <vector>
#include <list>
#include "../day12/print.h"
using namespace std;
template <typename type>
void my_swap (type& a, type& b) {
    type c = a;
    a = b;
    b = c;
}
template <typename iterator>
void my_sort (iterator begin, iterator end) {
    iterator p = begin;
    iterator last = end;
    --last;
    for (iterator i = begin, j = last; i != j;) {
        while (! (i == p || *p < *i))
            ++i;
        if (i != p) {
            my_swap (*p, *i);
            p = i;
        }
        while (!(j == p || *j < *p))
            --j;
        if (j != p){
            my_swap(*p, *j);
            p = j;
        }
    }
    iterator it = begin;
    ++it;
    if (p != begin && p != it)
        my_sort (begin, p);
    it = p;
    ++it;
    if (it != end && it != last)
        my_sort (it, end);
}
template <typename iterator, typename comparator>
void my_sort (iterator begin, iterator end,comparator cmp) {
    iterator p = begin;
    iterator last = end;
    --last;
    for (iterator i = begin, j = last; i != j;) {
        while (! (i == p || cmp(*p, *i)))
            ++i;
        if (i != p) {
            my_swap (*p, *i);
            p = i;
        }
        while (!(j == p || cmp(*j, *p)))
            --j;
        if (j != p){
            my_swap(*p, *j);
            p = j;
        }
    }
    iterator it = begin;
    ++it;
    if (p != begin && p != it)
        my_sort (begin, p, cmp);
    it = p;
    ++it;
    if (it != end && it != last)
        my_sort (it, end, cmp);
}
class CmpInt {
public:
    bool operator()(int a, int b) const {
        return a > b;
    }
};
int main (void) {
    int na[] = {10, 5, 78, 58, 41, 1, 36, 9};
    vector<int> vi (na, na + 8);
    list<int> li (na, na + 8);
    my_sort (na, na + 8);
    print (na, na + 8);
    my_sort (vi.begin(), vi.end());
    print (vi.begin (), vi.end ());
    my_sort (li.begin (),li.end(), CmpInt());
    print (li.begin(), li.end());

    return 0;
}
