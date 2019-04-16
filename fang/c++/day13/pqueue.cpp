#include <iostream>
#include <queue>
using namespace std;
class Student {
public:
    Student (const string& name, float score) :
        m_name (name), m_score (score) {}
    void print (void) const {
        cout << m_name << ',' << m_score <<endl;
    }
    bool operator < (const Student& student) const {
        return m_score > student.m_score;
    }
private:
    string m_name;
    float m_score;
};
class cmpInt {
public:
    bool operator() (int a, int b) {
        return a > b;
    }
};
int main (void) {
    priority_queue<int, deque<int >, cmpInt > pqi; //比普通队列多了一个参数
    pqi.push (23);
    pqi.push (12);
    pqi.push (23);
    pqi.push (27);
    pqi.push (19);
    while (! pqi.empty ()) {
        cout << pqi.top () << ' ';
        pqi.pop();
    }
    cout << endl;
    priority_queue<Student> pqs;
    pqs.push (Student ("张飞", 65));
    pqs.push (Student ("关羽", 60));
    pqs.push (Student ("吕布", 75));
    pqs.push (Student ("刘备", 100));
    pqs.push (Student ("曹操", 85));
    while (! pqs.empty () ){
        pqs.top().print();
        pqs.pop ();
    }
    return 0;
}
