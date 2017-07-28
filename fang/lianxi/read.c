#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
int main (void){
    char buf[PATH_MAX];
    memset(buf, 0, PATH_MAX);
    int fd = open ("1.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1){
        perror("open");
        return -1;
    }
    size_t len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    printf("%d\n", len-1);
    if (read(fd, buf, len-1) == -1){
        perror("read");
        return -1;
    }
    printf("%s\n", buf);
    return 0;
}
