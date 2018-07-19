#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

// 写锁测试
// 返回值：
//  1 - 可加写锁
//  0 - 不可加写锁
// -1 - 系统错误
int wtest (int fd, off_t start, off_t len) {
	struct flock lock;

	lock.l_type   = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start  = start;
	lock.l_len    = len;
	lock.l_pid    = -1;

	if (fcntl (fd, F_GETLK, &lock) == -1)
		return -1;

	if (lock.l_type == F_UNLCK)
		return 1;

	return 0;
}

// 加写锁
int wlock (int fd, off_t start, off_t len, int wait) {
	struct flock lock;

	lock.l_type   = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start  = start;
	lock.l_len    = len;
	lock.l_pid    = -1;

	return fcntl (fd, wait ? F_SETLKW : F_SETLK, &lock);
}

// 解锁
int ulock (int fd, off_t start, off_t len) {
	struct flock lock;

	lock.l_type   = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start  = start;
	lock.l_len    = len;
	lock.l_pid    = -1;

	return fcntl (fd, F_SETLK, &lock);
}

int main (int argc, char* argv[]) {
	if (argc < 2)
		goto usage;

	int lock = 0;
	if (argc > 2)
		if (! strcmp (argv[2], "-l"))
			lock = 1;
		else
			goto usage;

	int fd = open ("wlock.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (lock) {
		// 基于锁测试的非阻塞模式
		/*
		int unlock = 0;
		do {
			if ((unlock = wtest (fd, 0, 0)) == -1) {
				perror ("wtest");
				return -1;
			}

			if (! unlock) {
				printf ("该文件已被锁定，稍后再试...\n");
				// 空闲处理
				// ...
			}
		}	while (! unlock);

		if (wlock (fd, 0, 0, 0) == -1) {
			perror ("wlock");
			return -1;
		}
		*/
		// 基于锁失败的非阻塞模式
		/*
		while (wlock (fd, 0, 0, 0) == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				perror ("wlock");
				return -1;
			}

			printf ("该文件已被锁定，稍后再试...\n");
			// 空闲处理
			// ...
		}
		*/
		// 阻塞模式
		if (wlock (fd, 0, 0, 1) == -1) {
			perror ("wlock");
			return -1;
		}
	}

	size_t i, len = strlen (argv[1]);
	for (i = 0; i < len; i++) {
		if (write (fd, &argv[1][i], sizeof (argv[1][i])) == -1) {
			perror ("write");
			return -1;
		}
		sleep (1);
	}

	if (lock)
		if (ulock (fd, 0, 0) == -1) {
			perror ("ulock");
			return -1;
		}

	close (fd);

	return 0;

usage:
	fprintf (stderr, "用法：%s <字符串> [-l]\n", argv[0]);
	return -1;
}
