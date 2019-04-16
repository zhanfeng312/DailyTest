#include <iostream>
using namespace std;
void foo (void) throw (int, double, const char*) {
    //该函数可以被捕获的异常为int, double, const char*
    //	throw 1;
    //	throw 3.14;
	throw "Hello, Exception !";
}
int main (void) {
	try {
		foo ();
	}
	catch (int ex) {
		cout << ex << endl;
	}
	catch (double ex) {
		cout << ex << endl;
	}
	catch (const char* ex) {
		cout << ex << endl;
	}
	return 0;
}
