#include <stdio.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
	if (argc < 2) {
		fprintf (stderr, "用法：%s <文件>\n", argv[0]);
		return -1;
	}

	printf ("文件%s", argv[1]);
	if (access (argv[1], F_OK) == -1)
		printf ("不存在(%m)。\n");
	else {
		if (access (argv[1], R_OK) == -1)
			printf ("不可读(%m)，");
		else
			printf ("可读，");

		if (access (argv[1], W_OK) == -1)
			printf ("不可写(%m)，");
		else
			printf ("可写，");

		if (access (argv[1], X_OK) == -1)
			printf ("不可执行(%m)。\n");
		else
			printf ("可执行。\n");
	}

	return 0;
}
