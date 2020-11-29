#include <vector>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

typedef struct {
    string a;
    string b;
} A;

A a[] = {
    { "111", "222" }
};

int main(void)
{
    std::vector<A> signal_list_gb;
    
    signal_list_gb.push_back(a[0]);
    
    printf("%s\n", signal_list_gb[0].a.c_str());
    
    cout << signal_list_gb[0].a << endl;
    
    return 0;
}
