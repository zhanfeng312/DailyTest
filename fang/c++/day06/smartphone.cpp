#include <iostream>
using namespace std;
class Phone {
public:
    Phone (const string& numb) : m_numb (numb) {}
    void call (const string& numb) {  //电话的行为
        cout << m_numb << "致电" << numb << endl;
    }
private:
    string m_numb;
};
class Player {
public:
    Player (const string& media) : m_media (media) {}
    void play (const string& clip) {
        cout << m_media << "播放器播放" << clip << endl;
    }
private:
    string m_media;
};
class Computer {
public:
    Computer (const string& os) : m_os (os) {}
    void run (const string& prog) {
        cout << "在" << m_os << "上运行" << prog << endl;
    }
private
    tring m_os;
};














