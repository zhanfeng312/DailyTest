#include <iostream>
#include <set>
#include <fstream>
using namespace std;
int main (void) {
    ifstream ifs ("word.txt");
    set<string> ss;
    string word;
    while (ifs >> word)
        ss.insert (word);
    ifs.close();
    for (set<string>::iterator it = ss.begin ();
            it != ss.end (); ++it)
        cout << *it << endl;
        cout << "共"<<ss.size () << "个不同单词"            <<endl;
    return 0;
}
