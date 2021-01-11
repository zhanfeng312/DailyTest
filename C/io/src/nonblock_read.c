#include "io.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buffer[4096] = {'\0'};
    ssize_t size = 0;

    //设置非阻塞IO
    set_fl(STDIN_FILENO, O_NONBLOCK);
    
    sleep(5);

    size = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (size < 0) {
        perror("read error");
        exit(1);
    } else if (size == 0) { //ctrl + d
        printf("read finished!\n");
    } else {
        if (write(STDOUT_FILENO, buffer, size) != size) {
            perror("write error");
            exit(1);
        }
    }
    return 0;
}