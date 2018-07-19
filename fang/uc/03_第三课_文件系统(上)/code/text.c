#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main (void) {
	int fd = open ("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	char name[256] = "张飞";
	unsigned int age = 38;
	double salary = 20000;

	char buf[1024];
	sprintf (buf, "%s %u %.2lf\n", name, age, salary);

	if (write (fd, buf, strlen (buf) * sizeof (buf[0])) == -1) {
		perror ("write");
		return -1;
	}

	struct Employee {
		char name[256];
		unsigned int age;
		double salary;
	}	employee = {"赵云", 25, 8000};

	sprintf (buf, "%s %u %.2lf", employee.name, employee.age,
		employee.salary);

	if (write (fd, buf, strlen (buf) * sizeof (buf[0])) == -1) {
		perror ("write");
		return -1;
	}

	close (fd);

	if ((fd = open ("text.txt", O_RDONLY)) == -1) {
		perror ("open");
		return -1;
	}

	memset (buf, 0, sizeof (buf));

	if (read (fd, buf, sizeof (buf)) == -1) {
		perror ("read");
		return -1;
	}

	sscanf (buf, "%s%u%lf%s%u%lf", name, &age, &salary,
		employee.name, &employee.age, &employee.salary);

	printf ("姓名：%s\n", name);
	printf ("年龄：%u\n", age);
	printf ("工资：%.2lf\n", salary);
	printf ("员工：%s %u %.2lf\n", employee.name, employee.age,
		employee.salary);

	close (fd);

	return 0;
}
