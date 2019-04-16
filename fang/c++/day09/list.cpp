#include <iostream>
#include <stdexcept>
using namespace std;
//双向线性链表
class List {
public:
    // 构造过程中初始化为空链表
    List (void) : m_head (NULL), m_tail (NULL) {}
    // 析构过程中销毁剩余的节点
    ~List (void) {
        for (Node* next; m_head; m_head = next) {
            next = m_head->m_next;
            delete m_head;
        }
    }
    // 追加
    void append (int data) {
        m_tail = new Node (data, m_tail);
	if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
	else
	    m_head = m_tail;
    }
    // 插入
    void insert (size_t pos, int data) {
	for (Node* find = m_head; find;
	    find = find->m_next)
            if (pos-- == 0) {
                Node* node = new Node (data,
                        find->m_prev, find);
                if (node->m_prev)
                    node->m_prev->m_next = node;
		else
		    m_head = node;
                find->m_prev = node;
                return;
	    }
        throw out_of_range ("链表越界！");
    }
    // 删除
    void erase (size_t pos) {
	for (Node* find = m_head; find;
                find = find->m_next)
            if (pos-- == 0) {
                if (find->m_prev)
                    find->m_prev->m_next =
                        find->m_next;
                else
		    m_head = find->m_next;
	    if (find->m_next) //有后节点
                find->m_next->m_prev =
                    find->m_prev;
            else
		    m_tail = find->m_prev;
            delete find;
            return;
            }
        throw out_of_range ("链表越界！");
    }
    // 正向遍历
    void forward (void) const {
        for (Node* node = m_head; node;
                node = node->m_next)
            cout << node->m_data << ' ';
        cout << endli;
    }
    // 反向遍历
    void backward (void) const {
	for (Node* node = m_tail; node;
		node = node->m_prev)
	    cout << node->m_data << ' ';
	cout << endl;
    }
    // 下标访问  可以做左值
    int& operator[] (size_t index) {
	for (Node* find = m_head; find;
		find = find->m_next)
            if (index-- == 0)
                return find->m_data;
        throw out_of_range ("链表越界！");
    }
    const int& operator[] (size_t index) const {
        //先去常
        return const_cast<List&> (*this) [index];
    }
private:
    // 节点
    class Node {
        public:
            Node (int data = 0, Node* prev = NULL,
                    Node* next = NULL) : m_data (data),
            m_prev (prev), m_next (next) {}
            int m_data; // 数据
	    Node* m_prev; // 前指针
	    Node* m_next; // 后指针
    };
    Node* m_head; // 头指针
    Node* m_tail; // 尾指针
};
int main (void) {
    try {
        List list;
	list.append (10);
	list.append (30);
	list.append (50);
	list.append (60);
	list.append (80);
	list.insert (1, 20);
	list.insert (3, 40);
	list.insert (6, 70);
	list.forward ();
	list.backward ();
	list.erase (5);
	list.erase (5);
	list.erase (5);
	list.forward ();
        for (size_t i = 0; i < 5; ++i)
            ++list[i];
        const List& cr = list;
	for (size_t i = 0; i < 5; ++i)
            cout << /*++*/cr[i] << ' ';
        cout << endl;
    }
    catch (exception& ex) {
        cout << ex.what () << endl;
	return -1;
    }
    return 0;
}
