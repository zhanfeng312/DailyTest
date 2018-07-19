#include <iostream>
int main(void) {
    std::cout << "Hello World!" << std::endl;//，行尾，作用域 ，std命名空间
    int i;
    double d;
    char s[256];
    //scanf("%d%lf%s", &i, &d, s);
    std::cin >> i >> d >> s;
    //printf("%d %lf %s\n", i, d, s);
    std::cout << i <<' '<< d <<' '<< s <<'\n';
    return 0;
}
