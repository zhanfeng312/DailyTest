#include <stdio.h>
void func(char buf[])
{
    int i = 0;
    char *a = buf;
    while (*buf != '\0')
    {
        if (*buf >= 'A' && *buf <= 'Z')
            *buf += 32;
        buf++;
    }
    printf("%s\n", a);
}
int main (void)
{
    char array[] = "Fang";
    func (array);
    return 0;
}
