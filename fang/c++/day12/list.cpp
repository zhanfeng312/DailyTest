#include "print.h"
#include <list>
int main (void) {
    cout << "--------1------" << endl;
    list<int> li;
    li.push_back (34);
    li.push_back (28);
    li.push_back (34);
    li.push_back (34);
    li.push_back (55);
    li.push_back (34);
    print (li.begin (), li.end ());
    li.sort ();
    print (li.begin (), li.end ());
    li.unique();
    print (li.begin (), li.end ());
    cout << "--------2-----" << endl;
    list<int> li2;
    li2.push_front (100);
    li2.push_front (200);
    li2.push_front (300);
    list<int>::iterator pos = li.begin();  //迭代器pos
    ++pos;
    li.splice (pos, li2);
    /*list<int>::iterator start = li2.begin ();//迭代器start
    list<int>::iterator end = li2.end ();  //迭代器end
    --end;
    li.splice (pos, li2, start, end);*/
    print (li.begin (), li.end ());
    cout << li2.size () << endl;
    return 0;
}
