a.out : main.o student.o
	gcc main.o student.o
main.o : main.c
	gcc -c main.c
student.o : student.c
	gcc -c student.c
clean:
	rm *.o a.out
