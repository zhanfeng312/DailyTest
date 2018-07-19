#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 读锁测试
// 返回值：
//  1 - 可加读锁
//  0 - 不可加读锁
// -1 - 系统错误
int rtest (int fd, off_t start, off_t len) {
	struct flock lock;

	lock.l_type   = F_RDLCK;
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

// 加读锁
int rlock (int fd, off_t start, off_t len, int wait) {
	struct flock lock;

	lock.l_type   = F_RDLCK;
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
	int lock = 0;
	if (argc > 1)
		if (! strcmp (argv[1], "-l"))
			lock = 1;
		else
			goto usage;

	int fd = open ("wlock.txt", O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (lock) {
		// 基于锁测试的非阻塞模式
		/*
		int unlock = 0;
		do {
			if ((unlock = rtest (fd, 0, 0)) == -1) {
				perror ("rtest");
				return -1;
			}

			if (! unlock) {
				printf ("该文件已被锁定，稍后再试...\n");
				// 空闲处理
				// ...
			}
		}	while (! unlock);

		if (rlock (fd, 0, 0, 0) == -1) {
			perror ("rlock");
			return -1;
		}
		*/
		// 基于锁失败的非阻塞模式
		/*
		while (rlock (fd, 0, 0, 0) == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				perror ("rlock");
				return -1;
			}
	
			printf ("该文件已被锁定，稍后再试...\n");
			// 空闲处理
			// ...
		}
		*/
		// 阻塞模式
		if (rlock (fd, 0, 0, 1) == -1) {
			perror ("rlock");
			return -1;
		}
	}

	char buf[1024];
	ssize_t readed;

	while ((readed = read (fd, buf, sizeof (buf))) > 0)
		write (STDOUT_FILENO, buf, readed);
	printf ("\n");

	if (readed == -1) {
		perror ("read");
		return -1;
	}

	if (lock)
		if (ulock (fd, 0, 0) == -1) {
			perror ("ulock");
			return -1;
		}

	close (fd);

	return 0;

usage:
	fprintf (stderr, "用法：%s [-l]\n", argv[0]);
	return -1;
}
