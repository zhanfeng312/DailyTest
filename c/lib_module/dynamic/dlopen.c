#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main (void)
{
	void *handle = NULL;
	
	handle = dlopen("libbrowser_javascript_network_v8.so", RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	else
	{
		printf("%s\n", (char*)handle);
	}
	
	dlclose(handle);
	return 0;
}
