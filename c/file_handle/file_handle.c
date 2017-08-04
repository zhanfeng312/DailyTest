#include <stdio.h>

char g_buf[10] = {0};

static void test_handle_file()
{
	FILE *fp = NULL;
	int c;
	const char *file_name = "b.txt";

	fp = fopen(file_name, "a+");

	if (!fp){
		puts("file not exist!");
		return;
	}
    
	/*while ((c = fgetc(fp)) != EOF)
	{
		printf("%c", c);
	}*/
	
	while ((fgets(g_buf, sizeof(g_buf), fp)) != NULL){
		printf("%s", g_buf);
	}

	fclose(fp);
	fp = NULL;
}

int main(int argc, char *argv[])
{
	test_handle_file();

	return 0;
}

