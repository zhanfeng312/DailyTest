#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define DINERS 5 // 就餐人数

// 就餐者状态
typedef enum tag_State {
	THINKING, // 正在思考
	HUNGRY,   // 正在挨饿
	EATING    // 正在吃饭
}	ESTAT;

pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;

// 就餐者条件变量数组
pthread_cond_t g_conds[DINERS] = {
	PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER,
	PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER,
	PTHREAD_COND_INITIALIZER};

// 就餐者姓名数组
const char* g_names[DINERS] = {
	"  杨健", "  闵卫", "郭爱军", "张继文", "马志国"};

// 就餐者状态数组
ESTAT g_stats[DINERS] = {
	THINKING, THINKING, THINKING, THINKING, THINKING};

// 吃饭
void eat (int i) {
	int l = (i + 1) % DINERS; // 左邻
	int r = (i + DINERS - 1) % DINERS; // 右舍

	pthread_mutex_lock (&g_mtx);

	while (g_stats[l] == EATING || g_stats[r] == EATING) {
		g_stats[i] = HUNGRY;
		printf ("%s：快点吧，饿死我了~~~\n", g_names[i]);
		pthread_cond_wait (&g_conds[i], &g_mtx);
	}

	g_stats[i] = EATING;
	printf ("%s：终于可以吃一口了！\n", g_names[i]);

	pthread_mutex_unlock (&g_mtx);

	usleep ((rand () % 100) * 10000);
}

// 思考
void think (int i) {
	int l = (i + 1) % DINERS; // 左邻
	int r = (i + DINERS - 1) % DINERS; // 右舍

	pthread_mutex_lock (&g_mtx);

	g_stats[i] = THINKING;
	printf ("%s：吃饱了，开始思考...\n", g_names[i]);

	pthread_cond_signal (&g_conds[l]);
	pthread_cond_signal (&g_conds[r]);

	pthread_mutex_unlock (&g_mtx);

	usleep ((rand () % 100) * 10000);
}

// 就餐者线程
void* diner (void* arg) {
	int i = (int)arg; // 本人

	for (;;) {
		eat (i);
		think (i);
	}

	return NULL;
}

int main (void) {
	srand (time (NULL));

	pthread_attr_t attr;
	int error = pthread_attr_init (&attr);
	if (error) {
		fprintf (stderr, "pthread_attr_init: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_attr_setdetachstate (&attr,
		PTHREAD_CREATE_DETACHED)) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate: %s\n",
			strerror (error));
		return -1;
	}

	size_t i;
	pthread_t tid;
	for (i = 0; i < DINERS; ++i)
		if ((error = pthread_create (&tid, &attr, diner,
			(void*)i)) != 0) {
			fprintf (stderr, "pthread_create: %s\n", strerror (error));
			return -1;
		}

	getchar ();

	return 0;
}
