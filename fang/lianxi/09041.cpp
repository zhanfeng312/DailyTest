#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main (){
    vector<string> vi;
    string s("abc");
    for (size_t i = 0; i < 3; ++i)
        vi.push_back(s.substr(i, 3-i));
    vector<string>::iterator it = vi.begin();
    while (it!= vi.end()){
        cout << *it << ' ';
        it++;
    }
    cout << endl;
    return 0;
}
