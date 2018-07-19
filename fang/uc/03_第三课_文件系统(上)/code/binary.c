#include <stdio.h>
#include <fcntl.h>

int main (void) {
	int fd = open ("binary.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	char name[256] = "张飞";

	if (write (fd, name, sizeof (name)) == -1) {
		perror ("write");
		return -1;
	}

	unsigned int age = 38;

	if (write (fd, &age, sizeof (age)) == -1) {
		perror ("write");
		return -1;
	}

	double salary = 20000;

	if (write (fd, &salary, sizeof (salary)) == -1) {
		perror ("write");
		return -1;
	}

	struct Employee {
		char name[256];
		unsigned int age;
		double salary;
	}	employee = {"赵云", 25, 8000};

	if (write (fd, &employee, sizeof (employee)) == -1) {
		perror ("write");
		return -1;
	}

	close (fd);

	if ((fd = open ("binary.dat", O_RDONLY)) == -1) {
		perror ("open");
		return -1;
	}

	if (read (fd, name, sizeof (name)) == -1) {
		perror ("read");
		return -1;
	}

	printf ("姓名：%s\n", name);

	if (read (fd, &age, sizeof (age)) == -1) {
		perror ("read");
		return -1;
	}

	printf ("年龄：%u\n", age);

	if (read (fd, &salary, sizeof (salary)) == -1) {
		perror ("read");
		return -1;
	}

	printf ("工资：%.2lf\n", salary);

	if (read (fd, &employee, sizeof (employee)) == -1) {
		perror ("read");
		return -1;
	}

	printf ("员工：%s %u %.2lf\n", employee.name, employee.age,
		employee.salary);

	close (fd);

	return 0;
}
