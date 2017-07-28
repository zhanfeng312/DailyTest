#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main (void) {
	char cwd[PATH_MAX+1];
	if (! getcwd (cwd, sizeof (cwd))) {
		perror ("getcwd");
		return -1;
	}

	printf ("当前工作目录：%s\n", cwd);

	if (mkdir ("work", 0755) == -1) {
		perror ("mkdir");
		return -1;
	}

	if (chdir ("work") == -1) {
		perror ("chdir");
		return -1;
	}

	if (! getcwd (cwd, sizeof (cwd))) {
		perror ("getcwd");
		return -1;
	}

	printf ("当前工作目录：%s\n", cwd);

	if (mkdir ("empty", 0755) == -1) {
		perror ("mkdir");
		return -1;
	}

	if (rmdir ("empty") == -1) {
		perror ("rmdir");
		return -1;
	}

	if (rmdir ("../work") == -1) {
		perror ("rmdir");
		return -1;
	}

	return 0;
}
