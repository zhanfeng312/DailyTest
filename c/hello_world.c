#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* not strings.h !!! */
#include <stdarg.h>
#include <time.h>

#include <stdint.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/wait.h>		/* WEXITSTATUS */
#include <linux/sockios.h>	/* TIOCOUTQ */
#include <pthread.h>
#include <signal.h>


#define PROG_NAME   "daemon"

void		usage();
static void	sig_handle(int sig);
int			prog_exit(int eno);
void*		worker_thread();
void*		event_thread();



/*********************************************************************************
* Global Variables
*/
int		g_debug = 0;
int		g_system_done = 0;
/********************************************************************************/



//entry
int main(int argc, char* argv[])
{
    //signal deal start
	struct sigaction sa;
	sa.sa_flags = 0;
	
	sa.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sa, NULL);/* WIFEXITED and WEXITSTATUS after system need SIGCHLD */
	sa.sa_handler = SIG_IGN;
	sigaction (SIGPIPE, &sa, NULL);
	sa.sa_handler = sig_handle;
	sigaction (SIGHUP, &sa, NULL);
	sa.sa_handler = sig_handle;
	sigaction (SIGQUIT, &sa, NULL);
	sa.sa_handler = sig_handle;
	sigaction (SIGTERM, &sa, NULL);/* killall */
	sa.sa_handler = sig_handle;
	sigaction (SIGSTOP, &sa, NULL);
	sa.sa_handler = sig_handle;
	sigaction (SIGINT, &sa, NULL);
    //signal deal end
	
    //parse cmd start
    int c = 0;
    while ((c = getopt(argc, argv, "hd")) != EOF)
    {
        switch(c)
        {
            case 'h':
                usage();
                exit (1);
            case 'd':
                g_debug = 1;
                break;
            default:
                usage();
                exit (1);
        }
    }
    
    argv += optind;
    argc -= optind;
    //parse cmd end
    
    //fork start
    if (0 == g_debug)
    {
        pid_t pid;
        pid = fork();
        if(pid > 0){
            exit (0);
        }else if (pid == 0){
            printf("child process create success\n");
        }
        else{
            printf ("could not daemon mode !\n");
            exit (1);
        }
        setsid ();
    }
    //fork end

    //thread start
    pthread_t tid_worker_thread;
	pthread_t tid_event_thread;
	pthread_create(&tid_worker_thread, NULL, worker_thread, NULL);
	pthread_create(&tid_event_thread, NULL, event_thread, NULL);

	while (0 == g_system_done)
	{
		sleep(1);
	}

	pthread_join(tid_worker_thread, NULL);
	pthread_join(tid_event_thread, NULL);
    //thread end
    
	prog_exit(0);
	return 0;
}

void *worker_thread()
{
	if (g_debug) puts("worker_thread start ...");
	while (0 == g_system_done)
	{
		sleep(1);
	}
	if (g_debug) puts("worker_thread end ...");
	pthread_exit (NULL);
}

void *event_thread()
{
	if (g_debug) puts("event_thread start ...");
	while (0 == g_system_done)
	{	
		sleep(1);
	}
	if (g_debug) puts("event_thread end ...");
	pthread_exit (NULL);
}


void usage()
{
    fprintf(stderr, "-h: show help message\n");
    fprintf(stderr, "-g: open debug mode\n");
}

static void sig_handle(int sig)
{
	switch (sig)
	{
    	case SIGPIPE:
    		puts("");
    		break;
    	case SIGHUP:
    		puts("");
    		break;
    	case SIGINT:
    	case SIGTERM:
    	case SIGQUIT:
    	case SIGSTOP:
    		puts("");
    		if (g_debug) puts(PROG_NAME" end ...");
    		g_system_done = 1;
    		break;
	}
}


int prog_exit(int eno)
{	
	exit (eno);
}