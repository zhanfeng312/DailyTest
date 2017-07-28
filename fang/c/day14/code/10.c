/*
 * 函数练习
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
    char str[20] = {0};
    char ch = 0;
    float f_value = 0.0f;
    int value = atoi("234");
    double d_value = atof("23.4");
    printf("value是%d\n", value);
    printf("d_value是%lg\n", d_value);
    sscanf("25.8 a", "%g %c", &f_value, &ch);
    printf("%c %g\n", ch, f_value);
    sprintf(str, "%c %g", ch, f_value);
    printf("%s\n", str);
    return 0;
}

