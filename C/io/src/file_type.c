#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * lstat  软连接本身的信息
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s files\n", argv[0]);
        exit(1);
    }

    int i = 0;
    struct stat buff;
    for (i = 1; i < argc; i++) {
        memset(&buff, 0, sizeof(buff));
        if (lstat(argv[i], &buff) < 0) {
            perror("lstat error");
            continue;
        }
        printf("%-20s", argv[i]);
        if (S_ISREG(buff.st_mode)) {
            printf("normal file");
        } else if (S_ISDIR(buff.st_mode)) {
            printf("content");
        } else if (S_ISSOCK(buff.st_mode)) {
            printf("socket file");
        } else if (S_ISBLK(buff.st_mode)) {
            printf("block file");
        } else if (S_ISCHR(buff.st_mode)) {
            printf("character file");
        } else if (S_ISFIFO(buff.st_mode)) {
            printf("pipe file");
        } else if (S_ISLNK(buff.st_mode)) {
            printf("soft link file");
        } else {
            printf("unsupport file type");
        }
        printf("\n");
    }
    return 0;
}