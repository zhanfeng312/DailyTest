#include <stdio.h>

#include <unistd.h>

#include <sys/wait.h>


int main (void) {
	
	pid_t cpid[3];

	int i;

	
	for (i = 0; i < sizeof (cpid) / sizeof (cpid[0]); i++) {
		    cpid[i] = fork ();
		
	    if (cpid[i] == -1) {
			
               perror ("fork");
			
               return -1;
		
	    }

		
	    if (cpid[i] == 0) {
	
	       printf ("子进程：我是%u进程。我要退出了。\n", 
			getpid ());
		
	      return 0;
		
             }
	
        }

	
	for (i = 0; i < sizeof (cpid) / sizeof (cpid[0]); i++) {
		    printf ("父进程：我要等待%u进程...\n", cpid[i]);

			    pid_t pid = waitpid (cpid[i], 0, 0);
			    if (pid == -1) {
			
               perror ("waitpid");
			
	       return -1;

            }

		
            printf ("父进程：发现%u进程退出了。\n", pid);
	
        }


        return 0;
     
}
