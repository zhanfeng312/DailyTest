#include  "print.h"
#include <vector>
#include <algorithm>
template <typename iterator, typename type>
iterator myfind(iterator begin, iterator end,
        const type& key){
    for (; begin != end; ++begin)
        if (*begin == key)
            break;
    return begin;
}
bool cmpInt(const int& a, const int& b){
    return a > b;
}
class CmpInt{
    public:
        CmpInt(bool less = true):m_less(less){}
        bool operator() (const int& a, const int& b) const{
            return m_less ? (a < b): (a > b);
        }
    private:
        bool m_less;
int main (void){
    int ai[] = {10, 20, 30, 40, 50}; //数组也是向量
    vector<int> vi(ai, &ai[5]);
    print(vi.begin(), vi.end());
    vector<int>::iterator it = vi.begin();
    it = vi.insert(it + 1, 15);//在迭代器所指示的元素之前插
    print(vi.begin(), vi.end());
    ++++++it;
    vi.erase(it); //给谁，删谁,返回的是被删除元素的后一个迭代器
    print(vi.begin(), vi.end());
    cout << *it << endl;
    vi.insert(vi.begin(), 37);
    vi.insert(vi.begin() + 2, 43);
    vi.insert(vi.begin() + 4, 29);
    vi.push_back(18);
    vi.push_back(24);
    print(vi.begin(), vi.end());
    sort(vi.begin(), vi.end());
    print(vi.begin(), vi.end());//反向迭代器
    sort(vi.begin(), vi.end(), /*cmpInt*/CmpInt());
    print(vi.begin(), vi.end());
    it = myfind(vi.begin(), vi.end(), 18);
    if (it == vi.end())
        cout << "没找到!" << endl;
    else
        cout << "找到了: " << *it << endl;
    return 0;
}

