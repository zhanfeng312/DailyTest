#include <vector>
#include <deque>
#include <list>
#include "../day12/print.h"
template <typename IT1, typename IT2>
void my_copy (IT1 begin, IT1 end, IT2 to) {
    while (begin != end)
        *(to++) = *(begin++);
}
int main (void) {
    int arr1[5] = {10, 20, 30, 40, 50};
    int arr2[5];
    my_copy(arr1, arr1 + 5, arr2);
    print (arr2, arr2 + 5);
    vector<int> vec (5);
    //...
    print (vec.begin (), vec.end());
    deque<int> deq (5);
    //...
    print (deq.begin (), deq.end ());
    return 0;
}
