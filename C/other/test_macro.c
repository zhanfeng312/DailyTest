#include <stdio.h>
#include "../common/nt_common.h"

#define F1(R) #R
#define F2(R) F1(R)
#define A "192.168.51.100"

void test_macro(void);

int main(int argc, char *argv[])
{
    test_macro();
}

void test_macro(void)
{
//#ifndef _WIN32
#if !defined(_WIN32)
    if (A != NULL) {
        MY_LOG("F1(A) = %s", F1(A)); // ->A
        MY_LOG("F1(FANG) = %s", F1(FANG)); // ->FANG
        MY_LOG("F2(A) = %s", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"
    }
#else
    MY_LOG("win32 not support");
#endif
}