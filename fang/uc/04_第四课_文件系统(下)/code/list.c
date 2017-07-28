#include <stdio.h>
#include <dirent.h>
#include <errno.h>

int main (int argc, char* argv[]) {
	if (argc < 2) {
		fprintf (stderr, "用法：%s <目录>\n", argv[0]);
		return -1;
	}

	DIR* dp = opendir (argv[1]);
	if (! dp) {
		perror ("opendir");
		return -1;
	}

	errno = 0;
	struct dirent* de;

	for (de = readdir (dp); de; de = readdir (dp)) {
		switch (de -> d_type) {
			case DT_DIR:
				printf ("        目录：");
				break;
			case DT_REG:
				printf ("    普通文件：");
				break;
			case DT_LNK:
				printf ("      软链接：");
				break;
			case DT_BLK:
				printf ("      块设备：");
				break;
			case DT_CHR:
				printf ("    字符设备：");
				break;
			case DT_SOCK:
				printf ("Unix域套接字：");
				break;
			case DT_FIFO:
				printf ("    有名管道：");
				break;
			default:
				printf ("        未知：");
				break;
		}

		printf ("%s\n", de -> d_name);
	}

	if (errno) {
		perror ("readdir");
		return -1;
	}

	closedir (dp);

	return 0;
}
