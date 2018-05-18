#ifndef __CPP_TEST_H
#define __CPP_TEST_H

#include <string>
using namespace std;

class Test
{
public:
	Test(int age, string name);
	~Test();

	void set_age(int age);
	void set_name(string name);
	int get_age();
	string get_name();

private:
	int m_age;
	string m_name;
};

#endif //__CPP_TEST_H
