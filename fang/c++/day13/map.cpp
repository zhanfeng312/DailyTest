#include <iostream>
#include <map>
using namespace std;
class Candidate {
public:
    Candidate (const char* name = ""):
        m_name (name), m_votes (0) {}
    const string& name (void) const {
        return m_name;
    }
    size_t votes (void) const {
        return m_votes;
    }
    void vote (void) {
        ++m_votes;
    }
private:
    string m_name;
    size_t m_votes;
};
int main (void) {
    map<char, Candidate> mc;//映射
    mc.insert (pair<char, Candidate>('A',"张飞"));
    mc.insert (make_pair ('B', "赵云"));
    mc['C'] = "关羽";
    mc['D'] = "刘备";
    mc['E'] = "曹操";
    typedef map<char, Candidate>::iterator IT;
    typedef map<char, Candidate>::const_iterator CIT;
    for (size_t i = 0; i < 10;++i){
        for (CIT it = mc.begin () ;it != mc.end ();++it)
            cout << '(' << it->first <<')'
                << it->second.name () << ' ';
        cout << endl << "请投下宝贵的一票:" << flush;//把输出缓冲区刷新
        char key;
        cin >> key;
        IT it = mc.find (key);
        if (it == mc.end ()) {
            cout << "此票作废" << endl;
            continue;
        }
        it->second.vote ();
    }
    CIT win = mc.begin ();
    for (CIT it = mc.begin (); it != mc.end (); ++it){
        cout << it->second.name() << "获得"
            <<it->second.votes() << "票。" << endl;
        if (it->second.votes() > win->second.votes ())
            win = it;
    }
    cout <<"恭喜" << win->second.name() << "同学当选首席保洁员"
        << endl;
    return 0;
}
