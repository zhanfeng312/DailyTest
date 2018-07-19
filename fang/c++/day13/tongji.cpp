#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
using namespace std;
class CmpInt {
public:
    bool operator () (const string& a,
            const string& b) const {
        return strcasecmp (a.c_str (),
                b.c_str ()) < 0;
    }
};
class A {
public:
    A (int i) : m_i (i) {}
    bool operator < (const A& a) const {
        return m_i < a.m_i;
    }
private:
    int m_i;
};
int main (int argc, char* argv[]){
    if (argc < 2) {
        cerr << "用法:" << argv[0] << "<文件>" << endl;
        return -1;
    }
    ifstream ifs (argv[1]);
    if (! ifs) {
        perror ("打开文件失败!");
        return -1;
    }
    map<string, int, CmpInt> msi;
    string word;
    while (ifs >> word)
        ++msi[word];
    ifs.close ();
    for (map<string, int>::iterator it = msi.begin(); it != msi.end(); ++it)
        cout << it->first << " : " << it->second <<endl;
    return 0;
}

