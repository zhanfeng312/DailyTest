#include "cpp_test.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Test test(10);
    cout << test.get_age() << ":" << test.get_b() << endl;
    return 0;
}