target = test

CFLAGS += -shared -fPIC

LDFLAGS += -L.

LIBS += -lmyhello

$(target): libmyhello.so test.o
	gcc -o $@ test.o $(LDFLAGS) $(LIBS)

libmyhello.so:	hello.c hello.h
	gcc -o $@ $< $(CFLAGS)
    
test.o: test_libso.c
	gcc -o $@ -c $<

.PHONY: clean
clean:
	-rm  $(target) *.so *.o
