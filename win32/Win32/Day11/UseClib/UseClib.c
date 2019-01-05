

//c编译器什么都不要

//#pragma comment(lib, "../lib/Clib.lib")
//通知链接器 到 哪 拷贝源代码

int main ()
{
	int sum, sub;
	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}