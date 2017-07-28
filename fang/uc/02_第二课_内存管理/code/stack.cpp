#include <iostream>
using namespace std;

template<class T = int> class Stack {
public:
	Stack (void) : m_begin (sbrk (0)) {}

	~Stack (void) {
		brk (m_begin);
	}

	void push (const T& data) {
		*(T*)sbrk (sizeof (T)) = data;
	}

	void pop (void) {
		if (sbrk (0) != m_begin)
			sbrk (-sizeof (T));
	}

	bool top (T& data) {
		if (sbrk (0) != m_begin) {
			data = *((T*)sbrk (0) - 1);
			return true;
		}
		return false;
	}

private:
	void* m_begin;
};

int main (void) {
	Stack<> sn;

	for (int i = 0; i < 5; i++)
		sn.push (i + 1);

	for (int i; sn.top (i); sn.pop ())
		cout << i << ' ';
	cout << endl;

	Stack<const char*> ss;

	ss.push ("heze");
	ss.push ("zibo");
	ss.push ("jinan");
	ss.push ("weifang");
	ss.push ("qingdao");

	for (const char* s; ss.top (s); ss.pop ())
		cout << s << ' ';
	cout << endl;

	return 0;
}
