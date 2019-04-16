#include <iostream>
using namespace std;

int max_int (int x, int y) {
    return x > y ? x : y;
}
string max_str (string x, string y) {
    return x > y ? x : y;
}
int main (void) {
    cout << "请输入" << endl;
    string s1, s2;
    cin >> s1 >> s2;
    cout << "最大值" << max_str (s1, s2) << endl;

    return 0;
}
