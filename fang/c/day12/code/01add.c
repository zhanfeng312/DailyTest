#include "01add.h"
/*static*/ int result;  //静态全局变量的作用域被缩小到声明它的那个文件里面的所有语
void add(int value, int value1){
    result = value + value1;
}
