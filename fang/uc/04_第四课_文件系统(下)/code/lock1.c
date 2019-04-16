#include <stdio.h>
#include <string.h>
#include <fcntl.h>

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

int main (void) {
	printf ("进程标识(PID)：%u\n", getpid ());

	int fd = open ("lock.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	const char* text = "ABCDEFGHIJKLMNOPQR";
	if (write (fd, text, strlen (text) * sizeof (text[0])) == -1) {
		perror ("write");
		return -1;
	}

	// 对EFGH加读锁
	printf ("对EFGH加读锁");
	if (rlock (fd, 4, 4, 0) == -1) {
		printf ("失败：%m\n");
		return -1;
	}

	printf ("成功！\n");

	// 对MNOP加写锁
	printf ("对MNOP加写锁");
	if (wlock (fd, 12, 4, 0) == -1) {
		printf ("失败：%m\n");
		return -1;
	}

	printf ("成功！\n");

	printf ("按<回车>，解锁MN...");
	getchar ();
	// 解锁NM
	ulock (fd, 12, 2);

	printf ("按<回车>，解锁EFGH...");
	getchar ();
	// 解锁EFGH
	ulock (fd, 4, 4);

	close (fd);

	return 0;
}
