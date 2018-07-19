#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf ("%u进程：我在运行，按<Ctrl+C>或<Ctrl+\\>终止...\n",
		getpid ());

	for (;;);

	return 0;
}
