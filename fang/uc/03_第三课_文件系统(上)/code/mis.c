#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define USER_FILE "user.dat"

typedef int (*MENU) (void);
typedef int (*ONMENU) (void);

typedef struct tag_User {
	char name[256];
	char passwd[256];
}	USER;

void menuLoop (MENU menu, ONMENU onMenu[], size_t menus) {
	for (;;) {
		int idMenu = menu ();
		if (idMenu < 0 || menus <= idMenu)
			printf ("无效选择！\n");
		else if (onMenu[idMenu] () < 0)
			break;
	}
}

int menuLogin (void) {
	printf ("------------\n");
	printf ("学生管理系统\n");
	printf ("------------\n");
	printf ("[1] 注册    \n");
	printf ("[2] 登录    \n");
	printf ("[0] 退出    \n");
	printf ("------------\n");
	printf ("请选择：");

	int idMenu = -1;
	if (scanf ("%d", &idMenu) != 1)
		scanf ("%*[^\n]");

	return idMenu;
}

int menuStudent (void) {
	printf ("------------\n");
	printf ("学生管理系统\n");
	printf ("------------\n");
	printf ("[1] 增加学生\n");
	printf ("[2] 删除学生\n");
	printf ("[3] 浏览学生\n");
	printf ("[0] 注销    \n");
	printf ("------------\n");
	printf ("请选择：");

	int idMenu = -1;
	if (scanf ("%d", &idMenu) != 1)
		scanf ("%*[^\n]");

	return idMenu;
}

int onRegister (void) {
	USER userNew;
	printf ("用户名：");
	scanf ("%s", userNew.name);
	printf ("密码：");
	scanf ("%s", userNew.passwd);

	int fd = open (USER_FILE, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	USER userOld;
	ssize_t bytes;

	while ((bytes = read (fd, &userOld, sizeof (userOld))) > 0)
		if (! strcmp (userOld.name, userNew.name)) {
			printf ("用户名已存在，注册失败！\n");
			close (fd);
			return 0;
		}

	if (bytes == -1) {
		perror ("read");
		close (fd);
		return -1;
	}

	if (write (fd, &userNew, sizeof (userNew)) == -1) {
		perror ("write");
		close (fd);
		return -1;
	}

	close (fd);

	printf ("注册成功！\n");

	return 0;
}

int onAdd (void) {
	printf ("录入学生信息...\n");
	return 0;
}

int onDel (void) {
	printf ("删除学生信息...\n");
	return 0;
}

int onBrowse (void) {
	printf ("浏览学生信息...\n");
	return 0;
}

int onLogout (void) {
	return -1;
}

int onLogin (void) {
	USER userLog;
	printf ("用户名：");
	scanf ("%s", userLog.name);
	printf ("密码：");
	scanf ("%s", userLog.passwd);

	int fd = open (USER_FILE, O_RDONLY | O_CREAT, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	USER userOld;
	ssize_t bytes;

	while ((bytes = read (fd, &userOld, sizeof (userOld))) > 0)
		if (! strcmp (userOld.name, userLog.name))
			if (strcmp (userOld.passwd, userLog.passwd)) {
				printf ("密码错误，登录失败！\n");
				close (fd);
				return 0;
			}
			else
				break;

	if (bytes == -1) {
		perror ("read");
		close (fd);
		return -1;
	}

	if (bytes == 0) {
		printf ("用户名错误，登录失败！\n");
		close (fd);
		return 0;
	}

	close (fd);

	ONMENU onMenu[] = {onLogout, onAdd, onDel, onBrowse};
	menuLoop (menuStudent, onMenu, sizeof (onMenu) / sizeof (onMenu[0]));

	return 0;
}

int onQuit (void) {
	return -1;
}

int main (void) {
	ONMENU onMenu[] = {onQuit, onRegister, onLogin};
	menuLoop (menuLogin, onMenu, sizeof (onMenu) / sizeof (onMenu[0]));
	return 0;
}
