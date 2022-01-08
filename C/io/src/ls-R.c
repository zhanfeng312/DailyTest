#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

#define PATH_SIZE 256

static void DealFile(const char *name);

static void ReadDir(const char *dir)
{
    char path[PATH_SIZE];
    DIR *dp = opendir(dir);
    if (dp == NULL) {
        perror("opendir error.");
        exit(1);
    }

    struct dirent *ent = NULL;
    while ((ent = readdir(dp)) != NULL) {
        if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0)) {
            continue;
        }
        sprintf(path, "%s/%s", dir, ent->d_name);
        DealFile(path);
    }
    closedir(dp);
}

static void DealFile(const char *name)
{
    struct stat st;
    memset(&st, 0, sizeof(st));
    if (lstat(name, &st) == -1) {
        perror("lstat error.");
        return;
    }

    if (!S_ISDIR(st.st_mode)) {
        printf("%s\t\t%ld\n", name, st.st_size);
        return ;
    }
    ReadDir(name);
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        DealFile(".");
    } else {
        DealFile(argv[1]);
    }
    return 0;
}