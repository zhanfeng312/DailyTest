#include <iostream>
#include <vector>
using namespace std;
void print (const vector<int>& vi) {
    cout << "大小:" << vi.size() << endl; //元素的个数，而不是容量
    cout << "容量:" << vi.capacity() << endl;//以元素为单位
    for(vector<int>::const_iterator it = vi.begin();
            it != vi.end();++it)
        cout << *it << ' ';
    cout << endl;
}
int main (void) {
    vector<int> vi (5, 3);  //vi初始化5个元素，都为3
    print (vi);
    vector<int>::iterator it;
    it = vi.begin();
    *it = 4;
    print(vi);
    /*
    cout << "------1--------" << endl;
    vi.push_back (4);
    print (vi);
    vi[6] = 100;
    cout << vi[6] << endl;
    vi.push_back (5);
    cout << vi[6] << endl;
    print(vi);
    
    vi.resize (12);
    print (vi);
    
    vi.resize (2);
    print (vi);
    
    vi.clear ();
    print (vi);
    
    vi.reserve (20);
    print (vi);
    cout << vi[19] << endl;//只占个位置
    
    vi.reserve (5); // 0, 20 没我现在的大,不理你
    print (vi);
    */
    return 0;
}

