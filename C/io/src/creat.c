#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = creat(argv[1], 0666); //文件存在则清空,返回只写方式的文件描述符

    printf("fd = %d\n", fd);

    ssize_t ret = write(fd, "1234567", 7);
    if (ret == -1) {
        perror("write error.");
        exit(1);
    }
    printf("write return %ld\n", ret);

    char buf[32] = {0};
    ret = read(fd, buf, sizeof(buf)); //因为creat返回只写的文件描述符，所以read会报错
    if (ret == -1) {
        perror("read error.");
        exit(1);
    }
    printf("read the info: %s\n", buf);

    close(fd);
    return 0;
}
