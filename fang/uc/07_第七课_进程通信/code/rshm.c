#include <stdio.h>
#include <time.h>
#include <sys/shm.h>

int shmstat (int shmid) {
	struct shmid_ds shm;
	if (shmctl (shmid, IPC_STAT, &shm) == -1) {
		perror ("shmctl");
		return -1;
	}

	printf ("------------------------------------------------\n");
	printf ("                  共享内存信息\n");
	printf ("----+----------------+--------------------------\n");
	printf (" 所 | 键值           | 0x%08x\n", shm.shm_perm.__key);
	printf (" 有 | 有效属主ID     | %u\n", shm.shm_perm.uid);
	printf (" 者 | 有效属组ID     | %u\n", shm.shm_perm.gid);
	printf (" 及 | 有效创建者ID   | %u\n", shm.shm_perm.cuid);
	printf (" 其 | 有效创建组ID   | %u\n", shm.shm_perm.cgid);
	printf (" 权 | 权限字         | %#o\n", shm.shm_perm.mode);
	printf (" 限 | 序列号         | %u\n", shm.shm_perm.__seq);
	printf ("----+----------------+--------------------------\n");
	printf (" 大小(字节)          | %u\n", shm.shm_segsz);
	printf (" 最后加载时间        | %s", ctime (&shm.shm_atime));
	printf (" 最后卸载时间        | %s", ctime (&shm.shm_dtime));
	printf (" 最后改变时间        | %s", ctime (&shm.shm_ctime));
	printf (" 创建进程ID          | %u\n", shm.shm_cpid);
	printf (" 最后加载/卸载进程ID | %u\n", shm.shm_lpid);
	printf (" 当前加载计数        | %ld\n", shm.shm_nattch);
	printf ("---------------------+--------------------------\n");

	return 0;
}

int shmset (int shmid) {
	struct shmid_ds shm;
	if (shmctl (shmid, IPC_STAT, &shm) == -1) {
		perror ("shmctl");
		return -1;
	}

	shm.shm_perm.mode = 0600;
	shm.shm_segsz = 8192;

	if (shmctl (shmid, IPC_SET, &shm) == -1) {
		perror ("shmctl");
		return -1;
	}

	return 0;
}

int main (void) {
	printf ("获取共享内存...\n");

	key_t key = ftok (".", 100);
	if (key == -1) {
		perror ("ftok");
		return -1;
	}

	int shmid = shmget (key, 0, 0);
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

	shmstat (shmid);

	printf ("读取共享内存...\n");

	printf ("共享内存(0x%08x/%d)：%s\n", key, shmid, (char*)shmaddr);

	printf ("卸载共享内存...\n");

	if (shmdt (shmaddr) == -1) {
		perror ("shmdt");
		return -1;
	}

	shmstat (shmid);

	printf ("设置共享内存...\n");

	shmset (shmid);

	shmstat (shmid);

	printf ("大功告成！\n");

	return 0;
}
