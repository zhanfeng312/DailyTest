#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

int main (void) {
	printf ("创建共享内存...\n");

	key_t key = ftok (".", 100);
	if (key == -1) {
		perror ("ftok");
		return -1;
	}

	int shmid = shmget (key, 4096, 0644 | IPC_CREAT | IPC_EXCL);
	if (shmid == -1) {
		perror ("shmget");
		return -1;
	}

	printf ("加载共享内存...\n");

	void* shmaddr = shmat (shmid, NULL, 0);
	if (shmaddr == (void*)-1) {
		perror ("shmat");
		return -1;
	}

	printf ("写入共享内存...\n");

	sprintf (shmaddr, "我是%u进程写入的数据。", getpid ());

	printf ("按<回车>卸载共享内存(0x%08x/%d)...", key, shmid);
	getchar ();

	if (shmdt (shmaddr) == -1) {
		perror ("shmdt");
		return -1;
	}

	printf ("按<回车>销毁共享内存(0x%08x/%d)...", key, shmid);
	getchar ();

	if (shmctl (shmid, IPC_RMID, NULL) == -1) {
		perror ("shmctl");
		return -1;
	}

	printf ("大功告成！\n");

	return 0;
}
