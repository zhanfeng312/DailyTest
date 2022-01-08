#include "io.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN 1024

void Copy(int fdin, int fdout)
{
    char buffer[BUFFER_LEN];
    ssize_t size;

    //偏移到文件尾部
    lseek(fdin, 0L, SEEK_END);
    //偏移到文件头部
    lseek(fdin, 0L, SEEK_SET);
    while ((size = read(fdin, buffer, BUFFER_LEN)) > 0) {
        if (write(fdout, buffer, size) != size) {
            perror("write error\n");
            exit(1);
        }
    }

    if (size < 0) {
        perror("read error\n");
        exit(1); //return 1 非零表示异常
    }
}

void SetFileStatusFlag(int fd, int flag)
{
    //获得原来的文件状态标志
    int val = fcntl(fd, F_GETFL);
    //增加新的文件状态标志
    val |= flag;
    //重新设置文件状态标志(val为新的文件状态标志)
    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("fnctl error");
    }
}

void ClearFileStatusFlag(int fd, int flag)
{
    //获得原来的文件状态标志
    int val = fcntl(fd, F_GETFL);
    //清空指定的文件状态标志(置为0)
    val &= ~flag;
    //重新设置文件状态标志(val为新的文件状态标志)
    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("fnctl error");
    }
}