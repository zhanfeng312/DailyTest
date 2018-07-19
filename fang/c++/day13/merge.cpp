#include <iostream>
#include <list>
#include "print.h"
int main (void) {
    int ai1[] = {13, 23, 45, 65, 100};
    int ai2[] = {22, 23, 37, 50, 69, 109};
    list<int> li1 (ai1, ai1 + 5);
    list<int> li2 (ai2, ai2 + 6);
    print (li1.begin (), li1.end ());
    print (li2.begin (), li2.end ());
    li1.merge (li2);
    print (li1.begin (), li1.end ());
    print (li2.begin (), li2.end ());
    cout << "li2中的元素个数:" << li2.size () << endl;
    list<int>::iterator it = li1.begin ();
    li1.insert (it, 1000);
    li1.insert (it, 2000);
    print (li1.begin (), li1.end ());

    return 0;
}
