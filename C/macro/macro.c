#include <stdio.h>

#define F1(R) #R
#define F2(R) F1(R)

#define A "192.168.51.100"

int main (int argc, char *argv[])
{
#ifndef _WIN32
    printf("not win32 platform!\n");
    if (A != NULL)
    {
        printf("F1(A) = %s\n", F1(A)); // -> 
        printf("F2(A) = %s\n", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"
    }
#else
    printf("win32 platform!\n");
#endif
	return 0;
}