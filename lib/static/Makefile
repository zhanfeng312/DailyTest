target += test

LDFLAGS += -L.

LIBS += -lmyhello

$(target): libmyhello.a test.o
	gcc test.o $(LDFLAGS) $(LIBS) -o $(target)

libmyhello.a: hello.o
	ar cr libmyhello.a hello.o

hello.o: hello.c hello.h
	gcc -c hello.c

test.o:	test.c
	gcc -c test.c

clean:
	rm  $(target) *.a *.o
