#include <stdio.h>
#include "diamond.h"

int main (int argc, char* argv[]) {
	if (argc < 5) {
		fprintf (stderr, "Usage: %s <H> <D> <S> <C>\n", argv[0]);
		return -1;
	}

	diamond (atoi (argv[1]), atoi (argv[2]), atoi (argv[3]), *argv[4]);

	return 0;
}
