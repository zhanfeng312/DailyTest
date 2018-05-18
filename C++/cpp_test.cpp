#include "cpp_test.h"
#include <iostream>

Test::Test(int age, string name)
{
	m_age = age;
	m_name = name;
}

Test::~Test() {}

void Test::set_age(int age)
{
	m_age = age;
}

void Test::set_name(string name)
{
	m_name = name;
}

int Test::get_age()
{
	return m_age;
}

string Test::get_name()
{
	return m_name;
}