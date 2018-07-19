#include <stdio.h>
int main(int argc, char *argv[]){   //argc 表示字符串的个数
    int loop = 0;
    for (loop = 0; loop <= argc - 1; loop++) {
        printf("%s\n", argv[loop]);
    }

}
