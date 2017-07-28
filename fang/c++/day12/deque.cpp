#include <deque>
#include "print.h"
using namespace std;
int main (void) {
    deque<int> di;
    di.push_back (24);
    di.push_back (33);
    di.push_front (18);
    di.push_front (60);
    di.insert (di.begin () + 2, 47);
    print (di.begin (), di.end ());  //68, 18, 47, 24, 33
    di.pop_back ();
    di.pop_front ();
    di.erase (di.begin () + 1);
    print (di.begin (), di.end ());
    cout << di.size ()<< endl;


    return 0;
}
