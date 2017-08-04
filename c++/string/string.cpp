#include <iostream>
#include <string>

#include <cstdio> //for c

using namespace std;

int main (int argc, char **argv){
    
	const char *str1 = "fang";
    string s1 = str1;
	cout << s1 << ":" << s1.size() << ":" << s1.length() << endl;

	string s2 = "fangzhf";
	const char *str2 = s2.c_str();
	printf("%s\n", str2);

    return 0;
}