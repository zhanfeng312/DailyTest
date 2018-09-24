#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main (void)
{
	void *handle = NULL;
	void(*p_handle)(void) = NULL;
	char *error = NULL;
	
	handle = dlopen("libprint.so", RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	else
	{
		printf("%s\n", (char*)handle);
	}
	
	p_handle = dlsym(handle, "print");
	if ((error = dlerror()) != NULL)  {
		fprintf (stderr, "%s\n", error);
		exit(1);
	}
	(*p_handle)();
	
	dlclose(handle);
	return 0;
}
