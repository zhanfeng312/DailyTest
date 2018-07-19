#include <stdio.h>
#include <unistd.h>

int main (void) {
	char* path = "./argenv";
	char* file = "argenv";
	char* argv[] = {path, "hello", "world", NULL};
	char* envp[] = {"USER=unknown", "PATH=/tmp", NULL};
	/*
	if (execl (path, argv[0], argv[1], argv[2], argv[3]) == -1) {
		perror ("execl");
		return -1;
	}
	*//*
	if (execv (path, argv) == -1) {
		perror ("execv");
		return -1;
	}
	*//*
	if (execle (path, argv[0], argv[1], argv[2], argv[3], envp) == -1) {
		perror ("execle");
		return -1;
	}
	*//*
	if (execve (path, argv, envp) == -1) {
		perror ("execve");
		return -1;
	}
	*//*
	if (execlp (file, argv[0], argv[1], argv[2], argv[3]) == -1) {
		perror ("execlp");
		return -1;
	}
	*/
	if (execvp (file, argv) == -1) {
		perror ("execvp");
		return -1;
	}

	return 0;
}
