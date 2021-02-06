#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void test_file(void)
{
    FILE *fp = NULL;
    const char *fileName = "fang.txt";

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("open file failed\n");
        exit(1);
    }

    char buf[] = "Juan\n";
    printf("sizeof buf = %lu, strlen(buf) = %lu\n", sizeof(buf), strlen(buf));
    //size_t result = fwrite(buf, sizeof(char), sizeof(buf), fp); //返回实际写入的nmemb数目
    size_t result = fwrite(buf, sizeof(buf), sizeof(char), fp); //返回实际写入的nmemb数目
    printf("result is %lu\n", result);

    fclose(fp);
}

void test_content(void)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;

    if ((dir = opendir(".")) == NULL) {
        printf("opendir failed!\n");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
            continue;
        }
        printf("fileName is %s, type is %u, len is %u, offset is %lu\n",
               entry->d_name, entry->d_type, entry->d_reclen, entry->d_off); //目录为4, 文件为8
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    test_file();
    // test_content();

    (void)getchar();

    return 0;
}
