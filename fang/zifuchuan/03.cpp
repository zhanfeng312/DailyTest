#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
int main(void){
    vector<int> vi;
    int num;
    cin >> num;
    for (size_t i = 7; i <= num; i++){
        int m = i;
        if (m % 7 == 0){
            vi.push_back(m);
            continue;
        }
        while (m >= 7){
            if ( (m%10) == 7){
                vi.push_back(i);
                break;
            }
            m /= 10;
        }
    }
    vector<int>::iterator it = vi.begin();
    cout << vi.size() << ":(";
    for (;it != vi.end();)
        cout << *it++ << ' ';
    cout << ")"<< endl; 
    return 0;
}
