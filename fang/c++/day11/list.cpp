#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;
// 双向线性链表容器模板
template<typename T>
class List {
public:
	// 构造、析构、拷贝构造、拷贝赋值
	List (void) : m_head (NULL), m_tail (NULL) {}
	~List (void) {
            clear ();
	}
        //拷贝构造函数
	List (const List& that) : m_head (NULL),m_tail (NULL) {
            for (Node* node = that.m_head; node;
                    node = node->m_next)
                push_back (node->m_data);
        }
        //拷贝赋值运算
	List& operator= (const List& that) {
            if (&that != this) {
                list list (that);
                swap (m_head, list.m_head);
                swap (m_tail, list.m_tail);
            }
            return *this;
        }
	// 获取首元素
	T& front (void) {
            if (empty ())
                throw underflow_error ("链表下溢！");
	    return m_head->m_data;
	}
	const T& front (void) const {
            return const_cast<List*> (this)->front ();
	}
	// 向首部压入
	void push_front (const T& data) {
	    m_head = new Node (data, NULL, m_head);
	    if (m_head->m_next)
                m_head->m_next->m_prev = m_head;
	    else
		m_tail = m_head;
	}
	// 从首部弹出
	void pop_front (void) {
		if (empty ())
			throw underflow_error ("链表下溢！");
		Node* next = m_head->m_next;
		delete m_head;
		m_head = next;
		if (m_head)
			m_head->m_prev = NULL;
		else
			m_tail = NULL;
	}
	// 获取尾元素
	T& back (void) {
            if (empty ())
                throw underflow_error ("链表下溢！");
		return m_tail->m_data;
	}
	const T& back (void) const {
		return const_cast<List*> (this)->back ();
	}
	// 向尾部压入
	void push_back (const T& data) {
		m_tail = new Node (data, m_tail);
		if (m_tail->m_prev)
			m_tail->m_prev->m_next = m_tail;
		else
			m_head = m_tail;
	}
	// 从尾部弹出
	void pop_back (void) {
		if (empty ())
			throw underflow_error ("链表下溢！");
		Node* prev = m_tail->m_prev;
		delete m_tail;
		m_tail = prev;
		if (m_tail)
			m_tail->m_next = NULL;
		else
			m_head = NULL;
	}
	// 删除所有匹配元素
	void remove (const T& data) {
		for (Node* node = m_head, *next; node;
			node = next) {
			next = node->m_next;
			if (equal (node->m_data, data)) {
				if (node->m_prev)
					node->m_prev->m_next =
						node->m_next;
				else
					m_head = node->m_next;
				if (node->m_next)
					node->m_next->m_prev =
						node->m_prev;
				else
					m_tail = node->m_prev;
				delete node;
			}
		}
	}
	// 清空
	void clear (void) {
		for (Node* next; m_head; m_head = next) {
			next = m_head->m_next;
			delete m_head;
		}
		m_tail = NULL;
	}
	// 判空
	bool empty (void) const {
		return ! m_head && ! m_tail;
	}
	// 获取大小
	size_t size (void) const {
		size_t count = 0;
		for (Node* node = m_head; node;
			node = node->m_next)
			++count;
		return count;
	}
	// 插入输出流
	friend ostream& operator<< (ostream& os,
		const List& list) {
		for (Node* node = list.m_head; node;
			node = node->m_next)
			os << *node;
		return os;
	}
private:
	// 节点
	class Node {
	public:
		Node (const T& data = 0, Node* prev = NULL,
			Node* next = NULL) : m_data (data),
			m_prev (prev), m_next (next) {}
		friend ostream& operator<< (ostream& os,
			const Node& node) {
			return os << '(' << node.m_data << ')';
		}
		T m_data;     // 数据
		Node* m_prev; // 前指针
		Node* m_next; // 后指针
	};
	bool equal (const T& a, const T& b) const {
		return a == b;
	}
	Node* m_head; // 头指针
	Node* m_tail; // 尾指针
public:
	// 正向迭代器
	class Iterator {
	public:
		Iterator (Node* head = NULL,
			Node* tail = NULL, Node* node = NULL) :
			m_head (head), m_tail (tail),
			m_node (node) {}
		bool operator== (const Iterator& it) const {
			return m_node == it.m_node;
		}
		bool operator!= (const Iterator& it) const {
			return ! (*this == it);
		}
		Iterator& operator++ (void) {
			if (m_node)
				m_node = m_node->m_next;
			else
				m_node = m_head;
			return *this;
		}
		const Iterator operator++ (int) {
			Iterator old = *this;
			++*this;
			return old;
		}
		Iterator& operator-- (void) {
			if (m_node)
				m_node = m_node->m_prev;
			else
				m_node = m_tail;
			return *this;
		}
		const Iterator operator-- (int) {
			Iterator old = *this;
			--*this;
			return old;
		}
		T& operator* (void) const {
			return m_node->m_data;
		}
		T* operator-> (void) const {
			return &**this;
		}
	private:
		Node* m_head;
		Node* m_tail;
		Node* m_node;
		friend class List;
	};
	Iterator begin (void) {
		return Iterator (m_head, m_tail, m_head);
	}
	Iterator end (void) {
		return Iterator (m_head, m_tail);
	}
	Iterator insert (Iterator loc, const T& data) {
		if (loc == end ()) {
			push_back (data);
	   		return Iterator (m_head, m_tail,m_tail);
		}
		else {
			Node* node = new Node (data,
				loc.m_node->m_prev, loc.m_node);
			if (node->m_prev)
				node->m_prev->m_next = node;
			else
				m_head = node;
			node->m_next->m_prev = node;
			return Iterator (m_head, m_tail, node);
		}
	}
	Iterator erase (Iterator loc) {
		if (loc == end ())
			throw invalid_argument ("无效迭代器！");
		if (loc.m_node->m_prev)
			loc.m_node->m_prev->m_next =
				loc.m_node->m_next;
		else
			m_head = loc.m_node->m_next;
		if (loc.m_node->m_next)
			loc.m_node->m_next->m_prev =
				loc.m_node->m_prev;
		else
			m_tail = loc.m_node->m_prev;
		Node* next = loc.m_node->m_next;
		delete loc.m_node;
		return Iterator (m_head, m_tail, next);
	}
};
// 针对const char*的特化
template<>
bool List<const char*>::equal (const char* const& a,
	const char* const& b) const {
	return strcmp (a, b) == 0;
}
// 测试用例
int main (void) {
	try {
		List<int> list1;
		list1.push_front (20);
		list1.push_front (10);
		list1.push_back (30);
		list1.push_back (40);
		cout << list1 << endl;
		cout << list1.front () << ' ' <<
			list1.back () << endl;
		list1.pop_front ();
		list1.pop_back ();
		cout << list1 << endl;
		++list1.front ();
		--list1.back ();
		cout << list1 << endl;
		list1.push_back (21);
		list1.push_back (25);
		list1.push_back (21);
		list1.push_back (21);
		cout << list1 << endl;
		list1.remove (21);
		cout << list1 << endl;
		List<int> list2 = list1;
		cout << list2 << endl;
		list2.back () = 100;
		cout << list2 << endl;
		cout << list1 << endl;
		list2 = list1;
		cout << list2 << endl;
		list2.front () = 100;
		cout << list2 << endl;
		cout << list1 << endl;
		cout << list1.size () << endl;
		list1.clear ();
		cout << list1 << endl;
		cout << boolalpha << list1.empty () << endl;
//		List<string> list3;
		List<const char*> list3;
		list3.push_back ("beijing");
		list3.push_back ("tianjin");
		list3.push_front ("tianjin");
		list3.push_back ("shanghai");
		list3.push_back ("beijing");
		cout << list3 << endl;
		list3.remove (string ("beijing").c_str ());
		cout << list3 << endl;
		for (List<const char*>::Iterator it =
			list3.begin (); it != list3.end ();
			++it)
			cout << *it << ' ';
		cout << endl;
		List<const char*>::Iterator it =
			list3.begin ();
		it++;
		it = list3.insert (it, "chongqing");
		cout << list3 << endl;
		list3.erase (it);
		cout << list3 << endl;
	}
	catch (exception& ex) {
		cout << ex.what () << endl;
		return -1;
	}
	return 0;
}
