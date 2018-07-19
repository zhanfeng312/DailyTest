a.out : 01add.o 01sub.o 01.o 
	gcc 01add.o 01sub.o 01.o

01add.o : 01add.c
	gcc -c 01add.c
01sub.o : 01sub.c
	gcc -c 01sub.c
01.o : 01.c
	gcc -c 01.c
clean : 
	rm *.o a.out
