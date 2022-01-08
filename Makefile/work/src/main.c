#include "cal.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	int a = 10;
	int b = 5;
	printf("%d + %d = %d\n", a, b, add(a, b));
	printf("%d - %d = %d\n", a, b, sub(a, b));
	printf("%d * %d = %d\n", a, b, multi(a, b));
	printf("%d / %d = %d\n", a, b, div(a, b));
	return 0;
}
