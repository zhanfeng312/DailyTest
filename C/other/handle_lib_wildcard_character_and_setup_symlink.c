#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_SUPPORT_SO_NUM 10
#define BUF_SIZE 256

int get_max_so_index(char so_buf[][BUF_SIZE], int count_so, int *p_max_index)
{
    if (!so_buf || !p_max_index) {
        return -1;
    }

    FILE *fp = NULL;

    int index = 0;
    int max_size = 0;
    for (; index < count_so; index++) {
        if ((fp = fopen(so_buf[index], "rb")) == NULL) {
            printf("fopen failed!\n");
            return -1;
        }
        fseek(fp, 0L, SEEK_END); /* go to end of file */
        int file_size = ftell(fp);

        if (file_size > max_size) {
            *p_max_index = index;
            max_size = file_size;
        }

        fclose(fp);
    }
    fp = NULL;

    return 0;
}

int handle_lib_wildcard_character_and_setup_symlink(const char *pLibWildcardCharacter, const char *so_name)
{
    if (!pLibWildcardCharacter || !so_name) {
        printf("illegal argument!\n");
        return -1;
    }

    char so_buf[MAX_SUPPORT_SO_NUM][BUF_SIZE] = { { 0 } };
    char tmp_buf[BUF_SIZE] = { 0 };
    snprintf(tmp_buf, sizeof(tmp_buf) - 1, "%s", pLibWildcardCharacter);

    //find pLibWildcardCharacter content path and so wildcard character
    char *p = strrchr(tmp_buf, '/');
    if (!p) {
        printf("strrchr failed!\n");
        return -1;
    }
    else {
        *p = 0;
    }

    char target_content_path[BUF_SIZE] = { 0 };
    char so_wildcard_character[BUF_SIZE] = { 0 };
    snprintf(target_content_path, sizeof(target_content_path) - 1, "%s%s", tmp_buf, "/");
    snprintf(so_wildcard_character, sizeof(so_wildcard_character) - 1, "%s", p + 1);

    printf("target_content_path is %s, so wildcard character is %s\n", target_content_path, so_wildcard_character);

    //opendir and match so_name
    DIR *dirp;
    struct dirent *direntp;
    if ((dirp = opendir(target_content_path)) == NULL) {

        printf("opendir failed!\n");
        return -1;
    }

    int so_count = 0;
    while ((direntp = readdir(dirp)) != NULL) {

        if (!strncmp(direntp->d_name, so_wildcard_character, strlen(so_wildcard_character) - 1)) {

            snprintf(so_buf[so_count], sizeof(so_buf[so_count]) - 1, "%s%s", target_content_path, direntp->d_name);
            so_count++;
        }
        else
            continue;
    }
    closedir(dirp);

    printf("so_count is %d\n", so_count);

    int index = 0;
    for (; index < so_count; index++) {
        printf("match the so name is %s\n", so_buf[index]);
    }

    //get_max_so_index
    int max_so_index;
    get_max_so_index(so_buf, so_count, &max_so_index);

    printf("max index is %d\n", max_so_index);

    if (unlink(so_name) < 0) {

        printf("unlink so_name %s failed!\n", so_name);
        return -1;
    }
    if (symlink(so_buf[max_so_index], so_name) < 0) {

        printf("symlink failed!\n");
        return -1;
    }

    index = 0;
    for (; index < so_count; index++) {
        if (index == max_so_index) {
            continue;
        }
        if (unlink(so_buf[index]) < 0) {

            printf("so_name %s not exist", so_buf[index]);
            return -1;
        }
        if (symlink(so_buf[max_so_index], so_buf[index]) < 0) {
            printf("symlink failed!\n");
            return -1;
        }
    }

    printf("deal_lib_wildcard_character %s success!\n", pLibWildcardCharacter);

    return 0;
}

int main(int argc, char *argv[])
{
    handle_lib_wildcard_character_and_setup_symlink("/system/lib/libffi.so.*", "/system/lib/libffi.so");

    return 0;
}