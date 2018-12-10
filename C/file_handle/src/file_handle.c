#include "../my_common.h"

char g_buf[10] = {0};

static void test_handle_file()
{
	FILE *fp = NULL;
	const char *file_name = "b.txt";

	fp = fopen(file_name, "r");

	if (!fp){
		puts("file not exist!");
		return;
	}
	
	while ((fgets(g_buf, sizeof(g_buf), fp)) != NULL){
		printf("%s", g_buf);
	}

	fclose(fp);
	fp = NULL;
}

int main(int argc, char *argv[])
{
    fang_log("begin test\n");
    
	test_handle_file();

    fang_log("after test\n");

	return 0;
}
