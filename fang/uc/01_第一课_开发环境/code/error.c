#include <stdio.h>

#if (VERSION < 3)
	#error "Version too low !"
#elif (VERSION > 3)
	#warning "Version too high !"
#endif

int main (void) {
	printf ("VERSION=%d\n", VERSION);
	return 0;
}
