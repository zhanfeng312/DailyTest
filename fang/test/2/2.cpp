#include <iostream>
#include <vector>
using namespace std;
int main (){
    vector<int> vi;
    int a[] = {1, 2, 4, 5};
    int b[] = {1, 4, 5};
    size_t len1 = sizeof (a)/sizeof (a[0]);
    size_t len2 = sizeof (b)/sizeof (b[0]);
    for (size_t i = 0; i < len1; i++)
        for (size_t j = 0; j < len2; j++){
            if (a[i] == b[j]){
                vi.push_back(a[i]);
                break;
            }
        }
    cout << "交集为:" << endl;
    vector<int>::iterator it = vi.begin();
    while(it != vi.end())
        cout << *it++ << ' ';
    cout << endl;
    return 0;
}
