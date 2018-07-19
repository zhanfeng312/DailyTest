#include <stdio.h>
#include <limits.h>

int main (int argc, char* argv[]) {
	if (argc < 3) {
		fprintf (stderr, "用法：%s <文件> <软链接>\n", argv[0]);
		return -1;
	}

	if (symlink (argv[1], argv[2]) == -1) {
		perror ("symlink");
		return -1;
	}

	char slink[PATH_MAX+1] = {0};

	if (readlink (argv[2], slink,
		sizeof (slink) - sizeof (slink[0])) == -1) {
		perror ("readlink");
		return -1;
	}

	printf ("%s是%s的软链接。\n", argv[2], slink);

	return 0;
}
