#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void presskey (void) {
	printf ("查看/proc/%u/maps，按<回车>继续...", getpid ());
	getchar ();
}

int main (void) {
	printf ("1页 = %d字节\n", getpagesize ());

	char* pc = malloc (sizeof (char));
	printf ("pc = %p\n", pc);
	presskey ();

	free (pc);
	printf ("free(%p)\n", pc);
	presskey ();

	pc = malloc (sizeof (char));
	printf ("pc = %p\n", pc);
	presskey ();

	setbuf (stdout, NULL);
	size_t i = 0;
	for (;;) {
		printf ("向堆内存%p写...", &pc[i]);
		printf ("%c\n", pc[i++] =  (i % 26) + 'A');
	}

	free (pc);

	return 0;
}
