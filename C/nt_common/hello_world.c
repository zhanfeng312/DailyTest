#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* not strings.h !!! */
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
#include <sys/wait.h>       /* WEXITSTATUS */
#include <linux/sockios.h>  /* TIOCOUTQ */
#include <pthread.h>
#include <signal.h>

#define nt_log(fmt, ...) \
    do{ \
        fprintf(stderr, "%s %d " fmt, __FUNCTION__, __LINE__,  ##__VA_ARGS__);\
} while (0)

#define PROG_NAME   "daemon"

static void usage(void);
static void sig_handle(int sig);
static int prog_exit(int eno);
static void *worker_thread(void *arg);
static void *event_thread(void *arg);

/*********************************************************************************
* Global Variables
*/
int     g_debug = 0;
int     g_system_done = 0;
/********************************************************************************/

//entry
int main(int argc, char *argv[])
{
    printf("argc is %d\n", argc);

    //signal deal start
    struct sigaction sa;
    sa.sa_flags = 0;

    sa.sa_handler = SIG_IGN;
    sigaction(SIGCHLD, &sa, NULL);/* WIFEXITED and WEXITSTATUS after system need SIGCHLD */
    sigaction(SIGPIPE, &sa, NULL);

    sa.sa_handler = sig_handle;
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);/* killall */
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    //signal deal end

    //parse cmd start
    int c = 0;
    while ((c = getopt(argc, argv, "hd")) != EOF) {
        switch (c) {
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

    //thread start
    pthread_t tid_worker_thread;
    pthread_t tid_event_thread;
    pthread_create(&tid_worker_thread, NULL, worker_thread, NULL);
    pthread_create(&tid_event_thread, NULL, event_thread, NULL);

    while (0 == g_system_done) {
        sleep(1);
    }

    pthread_join(tid_worker_thread, NULL);
    pthread_join(tid_event_thread, NULL);
    //thread end

    prog_exit(0);
    return 0;
}

void *worker_thread(void *arg)
{
    if (g_debug) {
        printf("worker_thread start ...\n");
    }
    while (0 == g_system_done) {
        sleep(1);
    }
    if (g_debug) {
        printf("worker_thread end ...\n");
    }
    pthread_exit (NULL);
}

void *event_thread(void *arg)
{
    if (g_debug) {
        printf("event_thread start ...\n");
    }
    while (0 == g_system_done) {
        sleep(1);
    }
    if (g_debug) {
        printf("event_thread end ...\n");
    }
    pthread_exit (NULL);
}

void usage(void)
{
    fprintf(stderr, "------------------------------\n");
    nt_log("-h: show help message\n");
    nt_log("-g: open debug mode\n");
    fprintf(stderr, "------------------------------\n");
}

static void sig_handle(int sig)
{
    printf("receive signal %d\n", sig);
    switch (sig) {
        case SIGPIPE:
        case SIGHUP:
        case SIGINT:
        case SIGTSTP:
        case SIGTERM:
        case SIGQUIT:
        	if (g_debug) {
        	    printf(PROG_NAME" end ...");
        	}
            g_system_done = 1;
            break;
    }
}

int prog_exit(int eno)
{
    exit(eno);
}
