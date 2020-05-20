#include "dynamic_hello.h"
#include "cal.h"

#include <stdio.h>

void hello(const char *name)
{
	printf("Hello %s\n", name);

    printf ("1 + 2 = %d\n", add(1, 2));
}
