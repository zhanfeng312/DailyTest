#include <stdio.h>

int* foo (void) {
	int local = 10;
	return &local;
}

int main (void) {
	printf ("%d\n", *foo ());
	return 0;
}
