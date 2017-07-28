target += test

CFLAGS += -shared -fPIC

LDFLAGS += -L.

LIBS += -lmyhello

$(target):	libmyhello.so test.o
	gcc -o $(target) test.o $(LDFLAGS) $(LIBS)

libmyhello.so:	hello.c hello.h
	gcc -o libmyhello.so hello.c $(CFLAGS)
    
test.o: test.c
	gcc -c $<

.PHONY: clean
clean:
	-rm  $(target) *.so *.o
